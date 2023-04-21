namespace MinSharp.Compiler.LexicalAnalysis.Model
{
    /// <summary>
    /// Data structure to represent the source code text
    /// </summary>
    public class SourceText
    {
        /// <summary>
        /// Represents an empty source code
        /// </summary>
        public static SourceText Empty = new SourceText { Text = string.Empty };

        /// <summary>
        /// Source Code text
        /// </summary>
        public string Text { get; init; }

    }
}
