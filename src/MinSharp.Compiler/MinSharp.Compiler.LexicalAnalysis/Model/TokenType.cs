namespace MinSharp.Compiler.LexicalAnalysis.Model
{
    public enum TokenType
    {
        Error_Undefined = 0,
        WhiteSpace = 1,
        NewLine = 2,
        SingleLineComment = 3,
        MultiLineComment = 4,

        OpenBrace = 50,
        CloseBrace = 51,
        Coma = 52,
        SemiColon = 53,
        Colon = 54,
        OpenParentesis = 55,
        CloseParentesis = 56,
        OpenBraket = 57,
        CloseBraket = 58,
        QuestionMark = 59,
        Dot = 60,

        OperatorGreaterThan = 100,
        OperatorLessThan = 101,
        OperatorEquals = 102,
        OperatorNotEquals = 103,
        OperatorGreaterOrEqualsThan = 104,
        OperatorLessOrEqualsThan = 105,

        OperatorLogicalOr = 106,
        OperatorLogicalAnd = 107,
        OperatorLogicalNot = 108,

        OperatorBitwiseOr = 109,
        OperatorBitwiseAnd = 110,
        OperatorBitwiseNot = 111,
        OperatorBitwiseXor = 112,

        OperatorMultiplication = 113,
        OperatorExponentiation = 114,
        OperatorDivision = 115,
        OperatorRemainder = 116,
        OperatorAddition = 117,
        OperatorSubstraction = 118,

        OperatorIncrement = 119,
        OperatorDecrement = 120,

        OperatorNullConditional = 121,
        OperatorNullCoalescing = 122,

        OperatorAssignment = 200,
        OperatorAssignmentMultiply = 201,
        OperatorAssignmentDivide = 202,
        OperatorAssignmentReminder = 203,
        OperatorAssignmentAddition = 204,
        OperatorAssignmentSubstraction = 205,
        OperatorAssignmentBitwiseAnd = 206,
        OperatorAssignmentBitwiseOr = 207,
        OperatorAssignmentBitwiseXor = 208,

        OperatorLambda = 300,

        KeywordNamespace = 1000,
        KeywordType = 1001,
        KeywordData = 1002,
        KeywordInterface = 1003,
        KeywordFactory = 1004,
        KeywordWhile = 1005,
        KeywordDo = 1006,
        KeywordIf = 1007,
        KeywordElse = 1008,
        KeywordSwitch = 1009,
        KeywordReturn = 1010,
        KeywordThrow = 1011,
        KeywordBreak = 1012,
        KeywordVar = 1013,
        KeywordTrue = 1013,
        KeywordFalse = 1013,

        Identifier = 2000,

        StringLiteral = 3000,
        NumberLiteral = 4000,
        DateLiteral = 4001,


        ErrorUnclossedStringLiteral = 10000,
        ErrorInvalidEscapeSequence = 10001
    }
}