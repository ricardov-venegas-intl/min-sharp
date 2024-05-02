namespace MinSharp.Compiler.DataModels.Errors
{
    public class CompilationError
    {
        public CompilationError(CompilationUnitMetadata compilationUnit, int column, int line, CompilationErrorCode errorCode)
        {
            CompilationUnit = compilationUnit ?? throw new ArgumentNullException(nameof(compilationUnit));
            Column = column;
            Line = line;
            ErrorCode = errorCode;
        }

        public CompilationUnitMetadata CompilationUnit { get; private init; }
        public int Column { get; private init; }
        public int Line { get; private init; }
        public CompilationErrorCode ErrorCode { get; private init; }
    }
}
