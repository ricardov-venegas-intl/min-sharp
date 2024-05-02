namespace MinSharp.Compiler.DataModels.Errors
{
    public enum CompilationErrorCode
    {
        LexicalUnclosedStringLiteral,
        LexicalInvalidEscapeSequence,
        LexicalCommentNotClosed,
        LexicalInvalidNumberLiteral,
        LexicalUnrecognizedCharacter,
        LexicalUnclosedDateLiteral,
        LexicalInvalidDateTimeLiteral,

        SyntaxExpectedNamespaceKeyword,
        SyntaxExpectedIdentifier,
        SyntaxExpectedOpenCurlyBracket,
        SyntaxExpectedCloseCurlyBracket,
    }
}
