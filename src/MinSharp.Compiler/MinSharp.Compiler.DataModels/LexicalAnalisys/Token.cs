namespace MinSharp.Compiler.DataModels.LexicalAnalisys
{
    /// <summary>
    /// Data estructure representing a token in the source code.
    /// </summary>
    public class Token
    {
        /// <summary>
        /// Token Type.
        /// </summary>
        public TokenType TokenType { get; set; } = TokenType.Error_Undefined;

        /// <summary>
        /// Token Value.
        /// </summary>
        public SourceTextSpan Value { get; init; } = SourceTextSpan.Empty;

        /// <summary>
        /// Line number where the token is located.
        /// </summary>
        public int LineNumber { get; init; }

        /// <summary>
        /// Column Number where the token is located.
        /// </summary>
        public int ColumnNumber { get; init; }

        /// <summary>
        /// Indicates if the token is while space or comment (to be ignored for syntax analysis).
        /// </summary>
        public bool IsCommentOrWhiteSpace { get; set; } = false;

        /// <summary>
        /// Indicates if the token represents an error.
        /// </summary>
        public bool IsError {
            get
            {
                return TokenType switch
                {
                    TokenType.ErrorUnclosedStringLiteral
                    or TokenType.ErrorInvalidEscapeSequence
                    or TokenType.ErrorCommentNotClosed
                    or TokenType.ErrorInvalidNumberLiteral
                    or TokenType.UnrecognizedCharacter
                    or TokenType.ErrorUnclosedDateLiteral => true,
                    _ => false
                };
            }
        }

    }
}
