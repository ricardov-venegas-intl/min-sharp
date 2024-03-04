namespace MinSharp.Compiler.DataModels.Errors
{
    public enum CompilationErrorCode
    {
        LexicalUnclosedStringLiteral = 10000,
        LexicalInvalidEscapeSequence = 10001,
        LexicalCommentNotClosed = 10002,
        LexicalInvalidNumberLiteral = 10003,
        LexicalUnrecognizedCharacter = 10004,
        LexicalUnclosedDateLiteral = 10005,
        LexicalInvalidDateTimeLiteral = 10006,
    }
}
