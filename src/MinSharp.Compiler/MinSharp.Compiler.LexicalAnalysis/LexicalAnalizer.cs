using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using MinSharp.Compiler.Pipeline;

namespace MinSharp.Compiler.LexicalAnalysis
{
    public class LexicalAnalizer : ICompilationUnitPipelineStep
    {
        /// <inheritdoc/>
        public bool Execute(CompilationUnitContext context)
        {
            var takens = this.Parse(context.SourceText);
            context.TokenList.AddRange(takens);
            return context.TokenList.Any(t => t.IsError) == false;
        }

        /// <summary>
        /// Parse a source code text into an enumaration of tokens.
        /// </summary>
        /// <param name="code">source code to parse.</param>
        /// <returns>Enumeration of Codes</returns>
        private IEnumerable<Token> Parse(CompilationUnitSourceText sourceText)
        {
            var sourceCodeCursor = new SourceCodeCursor
            {
                SourceText = sourceText
            };

            Token? token = null;

            while (sourceCodeCursor.HasCurrentCharacter)
            {
                if (sourceCodeCursor.CurrentChar == '\r' || sourceCodeCursor.CurrentChar == '\n')
                {
                    yield return BuildNewLineToken(sourceCodeCursor);
                }
                else if (char.IsWhiteSpace(sourceCodeCursor.CurrentChar))
                {
                    yield return BuildWhiteSpaceToken(sourceCodeCursor);
                }
                else if (sourceCodeCursor.CurrentChar == '/' && sourceCodeCursor.NextCharacter == '/')
                {
                    yield return BuildSingleLineCommentToken(sourceCodeCursor);
                }
                else if (sourceCodeCursor.CurrentChar == '/' && sourceCodeCursor.NextCharacter == '*')
                {
                    yield return BuildMultipleLinesCommentToken(sourceCodeCursor);
                }
                else if (TryMatchTokenStrings(sourceCodeCursor, out token) && token != null)
                {
                    yield return token;
                }
                else if (sourceCodeCursor.CurrentChar == '_'
                    || char.IsLetter(sourceCodeCursor.CurrentChar)
                    || (sourceCodeCursor.CurrentChar == '@' && (sourceCodeCursor.NextCharacter == '_'
                    || char.IsLetterOrDigit(sourceCodeCursor.NextCharacter))))
                {
                    yield return BuildIdentifierToken(sourceCodeCursor);
                }
                else if (sourceCodeCursor.CurrentChar == '\"')
                {
                    yield return BuildStringLiteralToken(sourceCodeCursor);
                }
                else if (sourceCodeCursor.CurrentChar == '\'')
                {
                    yield return BuildDateLiteralToken(sourceCodeCursor);
                }
                else if (char.IsDigit(sourceCodeCursor.CurrentChar) == true)
                {
                    yield return BuildNumberLiteralToken(sourceCodeCursor);
                }
                else
                {
                    var startPosition = sourceCodeCursor.CurrentCharacterIndex;
                    var columnNumber = sourceCodeCursor.CurrentColumnIndex;
                    var lineNumber = sourceCodeCursor.CurrentLineIndex;
                    sourceCodeCursor.MoveNext();
                    yield return new Token
                    {
                        TokenType = TokenType.UnrecognizedCharacter,
                        Value = new SourceTextSpan
                        {
                            SourceText = sourceCodeCursor.SourceText,
                            StartPosition = startPosition,
                            Length = 1
                        },
                        ColumnNumber = columnNumber,
                        LineNumber = lineNumber,
                        IsCommentOrWhiteSpace = false
                    };
                }

            }
        }

        private bool TryMatchTokenStrings(SourceCodeCursor sourceCodeCursor, out Token? result)
        {
            foreach (var tokenString in StringToTokenTypeMap.TokenStrings)
            {
                if (sourceCodeCursor.IsMatchAtCurrentCharacter(tokenString))
                {
                    result = new Token
                    {
                        TokenType = StringToTokenTypeMap.Map[tokenString],
                        Value = new SourceTextSpan
                        {
                            SourceText = sourceCodeCursor.SourceText,
                            StartPosition = sourceCodeCursor.CurrentCharacterIndex,
                            Length = tokenString.Length
                        },
                        ColumnNumber = sourceCodeCursor.CurrentColumnIndex,
                        LineNumber = sourceCodeCursor.CurrentLineIndex,
                        IsCommentOrWhiteSpace = false
                    };
                    sourceCodeCursor.MoveNext(tokenString.Length);
                    return true;
                }
            }
            result = null;
            return false;
        }

        private Token BuildWhiteSpaceToken(SourceCodeCursor sourceCodeCursor)
        {
            return BuildToken(
                sourceCodeCursor,
                TokenType.WhiteSpace,
                (sourceCodeCursor) =>
                {
                    while (char.IsWhiteSpace(sourceCodeCursor.CurrentChar)
                            && sourceCodeCursor.CurrentChar != '\r'
                            && sourceCodeCursor.CurrentChar != '\n')
                    {
                        if (sourceCodeCursor.MoveNext() == false)
                        {
                            return;
                        }
                    }
                },
                true);
        }

        private Token BuildIdentifierToken(SourceCodeCursor sourceCodeCursor)
        {
            return BuildToken(
                sourceCodeCursor,
                TokenType.Identifier,
                (sourceCodeCursor) =>
                {
                    if (sourceCodeCursor.CurrentChar == '@')
                    {
                        sourceCodeCursor.MoveNext();
                    }
                    while (sourceCodeCursor.CurrentChar == '_'
                            || char.IsLetterOrDigit(sourceCodeCursor.CurrentChar))
                    {
                        if (sourceCodeCursor.MoveNext() == false)
                        {
                            return;
                        }
                    }
                },
                false);
        }

        private Token BuildNewLineToken(SourceCodeCursor sourceCodeCursor)
        {
            return BuildToken(
                sourceCodeCursor,
                TokenType.NewLine,
                (sourceCodeCursor) =>
                {
                    if (sourceCodeCursor.CurrentChar == '\r')
                    {
                        if (!sourceCodeCursor.MoveNext())
                        {
                            return;
                        }
                    }
                    if (sourceCodeCursor.CurrentChar == '\n')
                    {
                        if (!sourceCodeCursor.MoveNext())
                        {
                            return;
                        }
                    }
                },
                true);
        }

        private Token BuildSingleLineCommentToken(SourceCodeCursor sourceCodeCursor)
        {
            return BuildToken(
                sourceCodeCursor,
                TokenType.SingleLineComment,
                (sourceCodeCursor) =>
                {
                    while (sourceCodeCursor.CurrentChar != '\r' && sourceCodeCursor.CurrentChar != '\n')
                    {
                        if (sourceCodeCursor.MoveNext() == false)
                        {
                            break;
                        }
                    }
                },
                true);
        }

        private Token BuildStringLiteralToken(SourceCodeCursor sourceCodeCursor)
        {
            int tokenStartPosition = sourceCodeCursor.CurrentCharacterIndex;
            int tokenStartColumn = sourceCodeCursor.CurrentColumnIndex;
            int tokenStartLine = sourceCodeCursor.CurrentLineIndex;

            // Move to the next character
            if (sourceCodeCursor.MoveNext() == false)
            {
                return new Token
                {
                    TokenType = TokenType.ErrorUnclosedStringLiteral,
                    Value = new SourceTextSpan
                    {
                        SourceText = sourceCodeCursor.SourceText,
                        StartPosition = tokenStartPosition,
                        Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                    },
                    ColumnNumber = tokenStartColumn,
                    LineNumber = tokenStartLine,
                    IsCommentOrWhiteSpace = false
                };
            }

            while (sourceCodeCursor.CurrentChar != '\"')
            {
                if (sourceCodeCursor.CurrentChar == '\\')
                {
                    if (sourceCodeCursor.MoveNext() == false)
                    {
                        return new Token
                        {
                            TokenType = TokenType.ErrorUnclosedStringLiteral,
                            Value = new SourceTextSpan
                            {
                                SourceText = sourceCodeCursor.SourceText,
                                StartPosition = tokenStartPosition,
                                Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                            },
                            ColumnNumber = tokenStartColumn,
                            LineNumber = tokenStartLine,
                            IsCommentOrWhiteSpace = false
                        };
                    }
                }

                if (sourceCodeCursor.MoveNext() == false)
                {
                    return new Token
                    {
                        TokenType = TokenType.ErrorUnclosedStringLiteral,
                        Value = new SourceTextSpan
                        {
                            SourceText = sourceCodeCursor.SourceText,
                            StartPosition = tokenStartPosition,
                            Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                        },
                        ColumnNumber = tokenStartColumn,
                        LineNumber = tokenStartLine,
                        IsCommentOrWhiteSpace = false
                    };
                }

            }

            sourceCodeCursor.MoveNext();

            return new Token
            {
                TokenType = TokenType.StringLiteral,
                Value = new SourceTextSpan
                {
                    SourceText = sourceCodeCursor.SourceText,
                    StartPosition = tokenStartPosition,
                    Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                },
                ColumnNumber = tokenStartColumn,
                LineNumber = tokenStartLine,
                IsCommentOrWhiteSpace = false
            };
        }

        private Token BuildNumberLiteralToken(SourceCodeCursor sourceCodeCursor)
        {
            int tokenStartPosition = sourceCodeCursor.CurrentCharacterIndex;
            int tokenStartColumn = sourceCodeCursor.CurrentColumnIndex;
            int tokenStartLine = sourceCodeCursor.CurrentLineIndex;


            while (char.IsDigit(sourceCodeCursor.CurrentChar) == true || sourceCodeCursor.CurrentChar == '_')
            {
                if (sourceCodeCursor.MoveNext() == false)
                    break;
            }
            if (sourceCodeCursor.HasCurrentCharacter && sourceCodeCursor.CurrentChar == '.')
            {
                sourceCodeCursor.MoveNext();
                while (sourceCodeCursor.HasCurrentCharacter
                        && (char.IsDigit(sourceCodeCursor.CurrentChar) == true
                            || sourceCodeCursor.CurrentChar == '_'))
                {
                    sourceCodeCursor.MoveNext();
                }
            }
            if (sourceCodeCursor.HasCurrentCharacter
                && (sourceCodeCursor.CurrentChar == 'e' || sourceCodeCursor.CurrentChar == 'E'))
            {
                if (sourceCodeCursor.MoveNext() == false)
                {
                    return new Token
                    {
                        TokenType = TokenType.ErrorInvalidNumberLiteral,
                        Value = new SourceTextSpan
                        {
                            SourceText = sourceCodeCursor.SourceText,
                            StartPosition = tokenStartPosition,
                            Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                        },
                        ColumnNumber = tokenStartColumn,
                        LineNumber = tokenStartLine,
                        IsCommentOrWhiteSpace = false
                    };
                }
                if (sourceCodeCursor.CurrentChar == '+' || sourceCodeCursor.CurrentChar == '-')
                {
                    if (sourceCodeCursor.MoveNext() == false)
                    {
                        return new Token
                        {
                            TokenType = TokenType.ErrorInvalidNumberLiteral,
                            Value = new SourceTextSpan
                            {
                                SourceText = sourceCodeCursor.SourceText,
                                StartPosition = tokenStartPosition,
                                Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                            },
                            ColumnNumber = tokenStartColumn,
                            LineNumber = tokenStartLine,
                            IsCommentOrWhiteSpace = false
                        };
                    }
                }
                if (char.IsDigit(sourceCodeCursor.CurrentChar) == false)
                {
                    return new Token
                    {
                        TokenType = TokenType.ErrorInvalidNumberLiteral,
                        Value = new SourceTextSpan
                        {
                            SourceText = sourceCodeCursor.SourceText,
                            StartPosition = tokenStartPosition,
                            Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                        },
                        ColumnNumber = tokenStartColumn,
                        LineNumber = tokenStartLine,
                        IsCommentOrWhiteSpace = false
                    };
                }
                while (sourceCodeCursor.HasCurrentCharacter
                    && (char.IsDigit(sourceCodeCursor.CurrentChar) == true || sourceCodeCursor.CurrentChar == '_'))
                {
                    if (sourceCodeCursor.MoveNext() == false)
                    {
                        break;
                    }
                }
            }

            return new Token
            {
                TokenType = TokenType.NumberLiteral,
                Value = new SourceTextSpan
                {
                    SourceText = sourceCodeCursor.SourceText,
                    StartPosition = tokenStartPosition,
                    Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                },
                ColumnNumber = tokenStartColumn,
                LineNumber = tokenStartLine,
                IsCommentOrWhiteSpace = false
            };

        }

        private Token BuildMultipleLinesCommentToken(SourceCodeCursor sourceCodeCursor)
        {

            int tokenStartPosition = sourceCodeCursor.CurrentCharacterIndex;
            int tokenStartColumn = sourceCodeCursor.CurrentColumnIndex;
            int tokenStartLine = sourceCodeCursor.CurrentLineIndex;

            char previousChar = sourceCodeCursor.CurrentChar;
            sourceCodeCursor.MoveNext();
            while (previousChar != '*' || sourceCodeCursor.CurrentChar != '/')
            {
                previousChar = sourceCodeCursor.CurrentChar;
                if (sourceCodeCursor.MoveNext() == false)
                {
                    return new Token
                    {
                        TokenType = TokenType.ErrorCommentNotClosed,
                        Value = new SourceTextSpan
                        {
                            SourceText = sourceCodeCursor.SourceText,
                            StartPosition = tokenStartPosition,
                            Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                        },
                        ColumnNumber = tokenStartColumn,
                        LineNumber = tokenStartLine,
                        IsCommentOrWhiteSpace = true
                    };
                }
            }

            sourceCodeCursor.MoveNext();

            return new Token
            {
                TokenType = TokenType.MultiLineComment,
                Value = new SourceTextSpan
                {
                    SourceText = sourceCodeCursor.SourceText,
                    StartPosition = tokenStartPosition,
                    Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                },
                ColumnNumber = tokenStartColumn,
                LineNumber = tokenStartLine,
                IsCommentOrWhiteSpace = true
            };

        }


        private Token BuildDateLiteralToken(SourceCodeCursor sourceCodeCursor)
        {
            int tokenStartPosition = sourceCodeCursor.CurrentCharacterIndex;
            int tokenStartColumn = sourceCodeCursor.CurrentColumnIndex;
            int tokenStartLine = sourceCodeCursor.CurrentLineIndex;

            // Move to the next character
            if (sourceCodeCursor.MoveNext() == false)
            {
                return new Token
                {
                    TokenType = TokenType.ErrorUnclosedStringLiteral,
                    Value = new SourceTextSpan
                    {
                        SourceText = sourceCodeCursor.SourceText,
                        StartPosition = tokenStartPosition,
                        Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                    },
                    ColumnNumber = tokenStartColumn,
                    LineNumber = tokenStartLine,
                    IsCommentOrWhiteSpace = false
                };
            }

            while (sourceCodeCursor.CurrentChar != '\'')
            {
                if (sourceCodeCursor.MoveNext() == false)
                {
                    return new Token
                    {
                        TokenType = TokenType.ErrorUnclosedDateLiteral,
                        Value = new SourceTextSpan
                        {
                            SourceText = sourceCodeCursor.SourceText,
                            StartPosition = tokenStartPosition,
                            Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                        },
                        ColumnNumber = tokenStartColumn,
                        LineNumber = tokenStartLine,
                        IsCommentOrWhiteSpace = false
                    };
                }
            }

            sourceCodeCursor.MoveNext();

            return new Token
            {
                TokenType = TokenType.DateLiteral,
                Value = new SourceTextSpan
                {
                    SourceText = sourceCodeCursor.SourceText,
                    StartPosition = tokenStartPosition,
                    Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                },
                ColumnNumber = tokenStartColumn,
                LineNumber = tokenStartLine,
                IsCommentOrWhiteSpace = false
            };
        }

        private Token BuildToken(
            SourceCodeCursor sourceCodeCursor,
            TokenType tokenType,
            Action<SourceCodeCursor> traverseToken,
            bool isCommentOrWhiteSpace = false)
        {
            int tokenStartPosition = sourceCodeCursor.CurrentCharacterIndex;
            int tokenStartColumn = sourceCodeCursor.CurrentColumnIndex;
            int tokenStartLine = sourceCodeCursor.CurrentLineIndex;

            traverseToken(sourceCodeCursor);

            return new Token
            {
                TokenType = tokenType,
                Value = new SourceTextSpan
                {
                    SourceText = sourceCodeCursor.SourceText,
                    StartPosition = tokenStartPosition,
                    Length = sourceCodeCursor.CurrentCharacterIndex - tokenStartPosition
                },
                ColumnNumber = tokenStartColumn,
                LineNumber = tokenStartLine,
                IsCommentOrWhiteSpace = isCommentOrWhiteSpace
            };
        }
    }
}
