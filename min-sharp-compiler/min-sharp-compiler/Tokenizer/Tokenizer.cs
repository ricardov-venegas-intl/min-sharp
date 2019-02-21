using min_sharp_compiler.Interfaces;
using min_sharp_compiler.Types;
using System;
using System.Collections.Generic;

namespace min_sharp_compiler.Tokenizer
{
    /// <summary>
    /// Tokenizer Lexical analysis parser
    /// </summary>
    public class Tokenizer : ITokenizer
    {
        /// <summary>
        /// Parses a string into Tokens
        /// </summary>
        /// <param name="compilableUnit">Source code to compile</param>
        /// <returns>Enumeration of tokens resulting from parsing the source code</returns>
        public IEnumerable<Token> Parse(string compilableUnit)
        {
            var parserState = new ParserState(compilableUnit);
            while (parserState.MoveToNextChar())
            {
                parserState.StartToken();
                switch (parserState.CurrentChar)
                {
                    // Process New Line / Line Terminator
                    case '\r':
                        if (parserState.NextChar == '\n')
                        {
                            parserState.MoveToNextChar();
                        }
                        yield return parserState.BuildToken(TokenType.LineTerminator);
                        parserState.CurrentLine++;
                        parserState.CurrentColumn = 0;
                        break;

                    case '\n':
                        yield return parserState.BuildToken(TokenType.LineTerminator);
                        parserState.CurrentLine++;
                        parserState.CurrentColumn = 0;
                        break;

                    //Process white space
                    case char c when char.IsWhiteSpace(c):
                        while (char.IsWhiteSpace(parserState.NextChar) == true)
                        {
                            parserState.MoveToNextChar();
                        }
                        yield return parserState.BuildToken(TokenType.WhileSpace);
                        break;
                    // Process comment
                    case char c when c == '/' && parserState.NextChar == '/':
                        parserState.MoveToNextChar();
                        while (parserState.NextChar != '\r' && parserState.NextChar != '\n' && parserState.NextChar != '\0')
                        {
                            parserState.MoveToNextChar();
                        }
                        yield return parserState.BuildToken(TokenType.Comment);
                        break;
                    case '"':
                        parserState.MoveToNextChar();
                        while (parserState.CurrentChar != '"' && parserState.CurrentChar != '\0')
                        {
                            parserState.MoveToNextChar();
                            if (parserState.CurrentChar == '\\')
                            {
                                parserState.MoveToNextChar();
                            }
                        }
                        if (parserState.CurrentChar == '\0')
                        {
                            yield return parserState.BuildToken(TokenType.ErrorStringNotClosed);
                        }
                        else
                        {
                            yield return parserState.BuildToken(TokenType.StringLiteral);
                        }
                        break;
                    // Process identifiers and keywords
                    case char c when c == '@' || c == '_' || char.IsLetterOrDigit(c):
                        parserState.MoveToNextChar();
                        while (parserState.CurrentChar == '_' || char.IsLetterOrDigit(parserState.CurrentChar))
                        {
                            parserState.MoveToNextChar();
                        }
                        if (MemoryExtensions.Equals(parserState.CurrentTokenValue.Span, "using", StringComparison.InvariantCulture) == true)
                        {
                            yield return parserState.BuildToken(TokenType.KeywordUsing);
                        }
                        else if (MemoryExtensions.Equals(parserState.CurrentTokenValue.Span, "async", StringComparison.InvariantCulture) == true)
                        {
                            yield return parserState.BuildToken(TokenType.KeywordAsync);
                        }
                        else if (MemoryExtensions.Equals(parserState.CurrentTokenValue.Span, "await", StringComparison.InvariantCulture) == true)
                        {
                            yield return parserState.BuildToken(TokenType.KeywordAwait);
                        }
                        else if (MemoryExtensions.Equals(parserState.CurrentTokenValue.Span, "import", StringComparison.InvariantCulture) == true)
                        {
                            yield return parserState.BuildToken(TokenType.KeywordImport);
                        }
                        else if (MemoryExtensions.Equals(parserState.CurrentTokenValue.Span, "namespace", StringComparison.InvariantCulture) == true)
                        {
                            yield return parserState.BuildToken(TokenType.KeywordNamespace);
                        }
                        else 
                        {
                            yield return parserState.BuildToken(TokenType.Identifier);
                        }
                        break;
                    default:
                        break;

                }
            }
        }

        /// <summary>
        /// Represent the current state of the parser
        /// </summary>
        private class ParserState
        {
            /// <summary>
            /// Constructor
            /// </summary>
            /// <param name="compilableUnit">source code to parse</param>
            public ParserState(string compilableUnit)
            {
                this.Source = compilableUnit.AsMemory();
                this.CurrentLine = 1;
                this.CurrentColumn = 0;
                this.CurrentTokenStart = 0;
                this.CurrentPosition = -1;
            }
            /// <summary>
            /// Source Code MemorySpan (readonly)
            /// </summary>
            public ReadOnlyMemory<char> Source { get; set; }
            /// <summary>
            /// Current line being processed
            /// </summary>
            public int CurrentLine { get; set; }

            /// <summary>
            /// Current column being processed
            /// </summary>
            public int CurrentColumn { get; set; }

            /// <summary>
            /// Current position being processed (Index from Source)
            /// </summary>
            public int CurrentPosition { get; set; }

            /// <summary>
            /// Current char being processed
            /// </summary>
            public char CurrentChar { get; private set; }

            /// <summary>
            /// Next Char to process. \0 after the last character
            /// </summary>
            public char NextChar { get; private set; }

            /// <summary>
            /// Start position of the current Token
            /// </summary>
            public int CurrentTokenStart { get; set; }

            /// <summary>
            /// Start Column of the curren ttoken
            /// </summary>
            public int CurrentTokenStartColumn { get; set; }

            /// <summary>
            /// Start line of the current token
            /// </summary>
            public int CurrentTokenStartLine { get; set; }

            public ReadOnlyMemory<char> CurrentTokenValue
            {
                get
                {
                    return this.Source.Slice(this.CurrentTokenStart, this.CurrentPosition - this.CurrentTokenStart + 1);
                }
            }

            /// <summary>
            /// Move index to process nect character
            /// </summary>
            /// <returns>True if there is more chars to process</returns>
            public bool MoveToNextChar()
            {
                if (this.CurrentPosition < this.Source.Length - 1)
                {
                    this.CurrentColumn++;
                    this.CurrentPosition++;
                    this.CurrentChar = this.Source.Span[this.CurrentPosition];
                    this.NextChar = (this.CurrentPosition + 1 < this.Source.Length) ? this.Source.Span[this.CurrentPosition + 1] : '\0';
                    return true;
                }
                this.CurrentChar = '\0';
                this.NextChar = '\0';
                return false;
            }

            /// <summary>
            /// Starts process of a new token
            /// </summary>
            public void StartToken()
            {
                this.CurrentTokenStart = this.CurrentPosition;
                this.CurrentTokenStartColumn = this.CurrentColumn;
                this.CurrentTokenStartLine = this.CurrentLine;
            }

            /// <summary>
            /// Build a new token object
            /// </summary>
            /// <param name="tokenType">Token type of the new token</param>
            /// <returns>New token object</returns>
            public Token BuildToken(TokenType tokenType)
            {
                var newToken = new Token()
                {
                    TokenType = tokenType,
                    AbsolutePosition = CurrentTokenStart,
                    ColumnNumber = CurrentTokenStartColumn,
                    LineNumber = CurrentLine,
                    Value = this.Source.Slice(this.CurrentTokenStart, this.CurrentPosition - this.CurrentTokenStart + 1)
                };
                return newToken;
            }
        }
    }
}
