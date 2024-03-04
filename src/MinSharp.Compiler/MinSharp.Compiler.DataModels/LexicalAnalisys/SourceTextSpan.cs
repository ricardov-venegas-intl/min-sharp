namespace MinSharp.Compiler.DataModels.LexicalAnalisys
{
    /// <summary>
    /// Source Text Span.
    /// Represents a fragment of the source code.
    /// </summary>
    public class SourceTextSpan
    {
        /// <summary>
        /// Represents an empty source code text span.
        /// </summary>
        public static SourceTextSpan Empty =
            new SourceTextSpan
            {
                Length = 0,
                StartPosition = 0,
                SourceText = CompilationUnitSourceText.Empty,
            };

        private string? text = null;

        /// <summary>
        /// Original Source Text
        /// </summary>
        public CompilationUnitSourceText SourceText { get; init; } = CompilationUnitSourceText.Empty;

        /// <summary>
        /// Start position of the Span in the source text.
        /// </summary>
        public int StartPosition { get; init; } = -1;

        /// <summary>
        /// Length of the span
        /// </summary>
        public int Length { get; init; } = -1;

        /// <summary>
        /// Text of the span.
        /// </summary>
        public string Text
        {
            get
            {
                if (text == null)
                {
                    text = SourceText.Text.Substring(StartPosition, Length);
                }
                return text;
            }
        }
    }
}
