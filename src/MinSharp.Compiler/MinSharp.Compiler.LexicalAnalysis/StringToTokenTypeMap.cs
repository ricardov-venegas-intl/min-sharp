using MinSharp.Compiler.DataModels.LexicalAnalisys;

using System.Collections.ObjectModel;

namespace MinSharp.Compiler.LexicalAnalysis
{
    /// <summary>
    /// Maps String values to TokenType
    /// </summary>
    internal static class StringToTokenTypeMap
    {
        /// <summary>
        /// Map the string values of known tokens to TokenType
        /// </summary>
        public static IReadOnlyDictionary<string, TokenType> Map = new Dictionary<string, TokenType>
        {
            { "{", TokenType.OpenBrace},
            { "}", TokenType.CloseBrace},
            { ",", TokenType.Coma},
            { ";", TokenType.SemiColon},
            { ":", TokenType.Colon},
            { "(", TokenType.OpenParentesis},
            { ")", TokenType.CloseParentesis},
            { "[", TokenType.OpenBraket},
            { "]", TokenType.CloseBraket},
            { "?", TokenType.QuestionMark},
            { ".", TokenType.Dot},
            { ">", TokenType.OperatorGreaterThan},
            { "<", TokenType.OperatorLessThan},
            { "==", TokenType.OperatorEquals},
            { "!=", TokenType.OperatorNotEquals},
            { ">=", TokenType.OperatorGreaterOrEqualsThan},
            { "<=", TokenType.OperatorLessOrEqualsThan},
            { "||", TokenType.OperatorLogicalOr},
            { "&&", TokenType.OperatorLogicalAnd},
            { "!", TokenType.OperatorLogicalNot},
            { "|", TokenType.OperatorBitwiseOr},
            { "&", TokenType.OperatorBitwiseAnd},
            { "~", TokenType.OperatorBitwiseNot},
            { "^", TokenType.OperatorBitwiseXor},
            { "*", TokenType.OperatorMultiplication},
            { "**", TokenType.OperatorExponentiation},
            { "/", TokenType.OperatorDivision},
            { "%", TokenType.OperatorRemainder},
            { "+", TokenType.OperatorAddition},
            { "-", TokenType.OperatorSubstraction},
            { "++", TokenType.OperatorIncrement},
            { "--", TokenType.OperatorDecrement},
            { "?.", TokenType.OperatorNullConditional},
            { "??", TokenType.OperatorNullCoalescing},
            { "=", TokenType.OperatorAssignment},
            { "*=", TokenType.OperatorAssignmentMultiply},
            { "/=", TokenType.OperatorAssignmentDivide},
            { "%=", TokenType.OperatorAssignmentReminder},
            { "+=", TokenType.OperatorAssignmentAddition},
            { "-=", TokenType.OperatorAssignmentSubstraction},
            { "&=", TokenType.OperatorAssignmentBitwiseAnd},
            { "|=", TokenType.OperatorAssignmentBitwiseOr},
            { "^=", TokenType.OperatorAssignmentBitwiseXor},
            { "namespace", TokenType.KeywordNamespace},
            { "type", TokenType.KeywordType},
            { "data", TokenType.KeywordData},
            { "interface", TokenType.KeywordInterface},
            { "factory", TokenType.KeywordFactory},
            { "while", TokenType.KeywordWhile},
            { "do", TokenType.KeywordDo},
            { "if", TokenType.KeywordIf},
            { "else", TokenType.KeywordElse},
            { "switch", TokenType.KeywordSwitch},
            { "return", TokenType.KeywordReturn},
            { "throw", TokenType.KeywordThrow},
            { "break", TokenType.KeywordBreak},
            { "for", TokenType.KeywordFor},
            { "var", TokenType.KeywordVar},
            { "true", TokenType.KeywordTrue},
            { "false", TokenType.KeywordFalse},
            { "enum", TokenType.KeywordEnum }
        };

        /// <summary>
        /// List of known token strings ordered by length
        /// </summary>
        public static ReadOnlyCollection<string> TokenStrings = Map.Keys.OrderByDescending(x => x.Length).ToList().AsReadOnly();
    }
}
