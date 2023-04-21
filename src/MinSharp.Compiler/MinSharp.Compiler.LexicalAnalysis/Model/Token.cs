namespace MinSharp.Compiler.LexicalAnalysis.Model
{
    /// <summary>
    /// Data estructure representing a token in the source code.
    /// </summary>
    public class Token
    {
        /// <summary>
        /// Token Type.
        /// </summary>
        public TokenType TokenType { get; set; } = TokenType.Error;

        /// <summary>
        /// Token Value.
        /// </summary>
        public SourceTextSpan Value { get; init; }

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
    }
}
