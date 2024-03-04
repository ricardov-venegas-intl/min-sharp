namespace MinSharp.Compiler.DataModels
{
    /// <summary>
    /// Data structure to represent the source code text
    /// </summary>
    public class CompilationUnitSourceText
    {
        /// <summary>
        /// Represents an empty source code
        /// </summary>
        public static CompilationUnitSourceText Empty = new CompilationUnitSourceText { Text = string.Empty };

        /// <summary>
        /// Source Code text
        /// </summary>
        public string Text { get; init; } = string.Empty;

    }
}
