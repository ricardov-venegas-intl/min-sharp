using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MinSharp.Compiler.LexicalAnalysis.Model;

namespace MinSharp.Compiler.LexicalAnalysis
{
    public class LexicalAnalizer
    {
        private static Dictionary<string, TokenType> stringToTokenTypeMap = new Dictionary<string, TokenType>
        {
            { "{", TokenType.OpenBrace},
            { "}", TokenType.CloseBrace},
            { ",", TokenType.Coma},
            { ";", TokenType.SemiColon},
            { ":", TokenType.Colon},
            { "(", TokenType.OpenParentesis},
            { ")", TokenType.CloseParentesis},
            { "[", TokenType.OpenBraket},
            { "]", TokenType.CloseBraket},
            { "?", TokenType.QuestionMark},
            { ".", TokenType.Dot},
            { ">", TokenType.OperatorGreaterThan},
            { "<", TokenType.OperatorLessThan},
            { "==", TokenType.OperatorEquals},
            { "!=", TokenType.OperatorNotEquals},
            { ">=", TokenType.OperatorGreaterOrEqualsThan},
            { "<=", TokenType.OperatorLessOrEqualsThan},
            { "||", TokenType.OperatorLogicalOr},
            { "&&", TokenType.OperatorLogicalAnd},
            { "!", TokenType.OperatorLogicalNot},
            { "|", TokenType.OperatorBitwiseOr},
            { "&", TokenType.OperatorBitwiseAnd},
            { "~", TokenType.OperatorBitwiseNot},
            { "^", TokenType.OperatorBitwiseXor},
            { "*", TokenType.OperatorMultiplication},
            { "**", TokenType.OperatorExponentiation},
            { "/", TokenType.OperatorDivision},
            { "%", TokenType.OperatorRemainder},
            { "+", TokenType.OperatorAddition},
            { "-", TokenType.OperatorSubstraction},
            { "++", TokenType.OperatorIncrement},
            { "--", TokenType.OperatorDecrement},
            { "?.", TokenType.OperatorNullConditional},
            { "??", TokenType.OperatorNullCoalescing},
            { "=", TokenType.OperatorAssignment},
            { "*=", TokenType.OperatorAssignmentMultiply},
            { "/=", TokenType.OperatorAssignmentDivide},
            { "%=", TokenType.OperatorAssignmentReminder},
            { "+=", TokenType.OperatorAssignmentAddition},
            { "-=", TokenType.OperatorAssignmentSubstraction},
            { "&=", TokenType.OperatorAssignmentBitwiseAnd},
            { "|=", TokenType.OperatorAssignmentBitwiseOr},
            { "^=", TokenType.OperatorAssignmentBitwiseXor},
            { "namespace", TokenType.KeywordNamespace},
            { "type", TokenType.KeywordType},
            { "data", TokenType.KeywordData},
            { "interface", TokenType.KeywordInterface},
            { "factory", TokenType.KeywordFactory},
            { "while", TokenType.KeywordWhile},
            { "do", TokenType.KeywordDo},
            { "if", TokenType.KeywordIf},
            { "else", TokenType.KeywordElse},
            { "switch", TokenType.KeywordSwitch},
            { "return", TokenType.KeywordReturn},
            { "throw", TokenType.KeywordThrow},
            { "break", TokenType.KeywordBreak},
            { "var", TokenType.KeywordVar},
            { "true", TokenType.KeywordTrue},
            { "false", TokenType.KeywordFalse},
        };

        private static string[] mappedTokenStrings = stringToTokenTypeMap.Keys.OrderByDescending(x => x.Length).ToArray();

        /// <summary>
        /// Parse a source code text into an enumaration of tokens.
        /// </summary>
        /// <param name="code">source code to parse.</param>
        /// <returns>Enumeration of Codes</returns>
        public IEnumerable<Token> Parse(string code)
        {
            var sourceCodeCursor = new SourceCodeCursor
            {
                SourceText = new SourceText { Text = code }                
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
                    || (sourceCodeCursor.CurrentChar == '@' && (sourceCodeCursor.NextCharacter== '_'
                    || char.IsLetterOrDigit(sourceCodeCursor.NextCharacter))))
                {
                    yield return BuildIdentifierToken(sourceCodeCursor);
                }
                else if (sourceCodeCursor.CurrentChar == '\"')
                {
                    yield return BuildStringLiteralToken(sourceCodeCursor);
                }
                else {
                    throw new InvalidOperationException();
                }

            }
        }

        private bool TryMatchTokenStrings(SourceCodeCursor sourceCodeCursor, out Token? result)
        {
            foreach (var tokenString in mappedTokenStrings)
            {
                if (sourceCodeCursor.IsMatchAtCurrentCharacter(tokenString))
                {
                    result = new Token
                    {
                        TokenType = stringToTokenTypeMap[tokenString],
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
            var validEscapeSequence = "\\trnbf0\"";

            int tokenStartPosition = sourceCodeCursor.CurrentCharacterIndex;
            int tokenStartColumn = sourceCodeCursor.CurrentColumnIndex;
            int tokenStartLine = sourceCodeCursor.CurrentLineIndex;

            // Move to the next character
            if (sourceCodeCursor.MoveNext() == false)
            {
                return new Token
                {
                    TokenType = TokenType.ErrorUnclossedStringLiteral,
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
                            TokenType = TokenType.ErrorUnclossedStringLiteral,
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
                        TokenType = TokenType.ErrorUnclossedStringLiteral,
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



        private Token BuildMultipleLinesCommentToken(SourceCodeCursor sourceCodeCursor)
        {
            return BuildToken(
                sourceCodeCursor,
                TokenType.MultiLineComment,
                (sourceCodeCursor) =>
                {
                    char previousChar = sourceCodeCursor.CurrentChar;
                    sourceCodeCursor.MoveNext();
                    while (previousChar != '*' || sourceCodeCursor.CurrentChar != '/')
                    {
                        previousChar = sourceCodeCursor.CurrentChar;
                        if (sourceCodeCursor.MoveNext() == false)
                        {
                            throw new Exception("Comment not closed");
                        }
                    }
                    sourceCodeCursor.MoveNext();
                },
                true);
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
