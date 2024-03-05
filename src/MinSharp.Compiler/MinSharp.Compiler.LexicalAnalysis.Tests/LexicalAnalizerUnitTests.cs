using Microsoft.VisualStudio.TestTools.UnitTesting;

using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using MinSharp.Compiler.Pipeline;
using System.Linq;

namespace MinSharp.Compiler.LexicalAnalysis.Tests
{
    [TestClass]
    public class LexicalAnalizerUnitTests
    {
        [DataTestMethod]
        [DataRow(" ", TokenType.WhiteSpace, true)]
        [DataRow("\n", TokenType.NewLine, true)]
        [DataRow("\r", TokenType.NewLine, true)]
        [DataRow("\r\n", TokenType.NewLine, true)]
        [DataRow("// Lorem Ipsum", TokenType.SingleLineComment, true)]
        [DataRow("/* Lorem \r\n Ipsum */", TokenType.MultiLineComment, true)]
        [DataRow("/* Lorem \r\n Ipsum ", TokenType.ErrorCommentNotClosed, true)]
        [DataRow("{", TokenType.OpenBrace, false)]
        [DataRow("}", TokenType.CloseBrace, false)]
        [DataRow(",", TokenType.Coma, false)]
        [DataRow(";", TokenType.SemiColon, false)]
        [DataRow(":", TokenType.Colon, false)]
        [DataRow("(", TokenType.OpenParentesis, false)]
        [DataRow(")", TokenType.CloseParentesis, false)]
        [DataRow("[", TokenType.OpenBraket, false)]
        [DataRow("]", TokenType.CloseBraket, false)]
        [DataRow("?", TokenType.QuestionMark, false)]
        [DataRow(".", TokenType.Dot, false)]
        [DataRow(">", TokenType.OperatorGreaterThan, false)]
        [DataRow("<", TokenType.OperatorLessThan, false)]
        [DataRow("==", TokenType.OperatorEquals, false)]
        [DataRow("!=", TokenType.OperatorNotEquals, false)]
        [DataRow(">=", TokenType.OperatorGreaterOrEqualsThan, false)]
        [DataRow("<=", TokenType.OperatorLessOrEqualsThan, false)]
        [DataRow("||", TokenType.OperatorLogicalOr, false)]
        [DataRow("&&", TokenType.OperatorLogicalAnd, false)]
        [DataRow("!", TokenType.OperatorLogicalNot, false)]
        [DataRow("|", TokenType.OperatorBitwiseOr, false)]
        [DataRow("&", TokenType.OperatorBitwiseAnd, false)]
        [DataRow("~", TokenType.OperatorBitwiseNot, false)]
        [DataRow("^", TokenType.OperatorBitwiseXor, false)]
        [DataRow("*", TokenType.OperatorMultiplication, false)]
        [DataRow("**", TokenType.OperatorExponentiation, false)]
        [DataRow("/", TokenType.OperatorDivision, false)]
        [DataRow("%", TokenType.OperatorRemainder, false)]
        [DataRow("+", TokenType.OperatorAddition, false)]
        [DataRow("-", TokenType.OperatorSubstraction, false)]
        [DataRow("++", TokenType.OperatorIncrement, false)]
        [DataRow("--", TokenType.OperatorDecrement, false)]
        [DataRow("?.", TokenType.OperatorNullConditional, false)]
        [DataRow("??", TokenType.OperatorNullCoalescing, false)]
        [DataRow("=", TokenType.OperatorAssignment, false)]
        [DataRow("*=", TokenType.OperatorAssignmentMultiply, false)]
        [DataRow("/=", TokenType.OperatorAssignmentDivide, false)]
        [DataRow("%=", TokenType.OperatorAssignmentReminder, false)]
        [DataRow("+=", TokenType.OperatorAssignmentAddition, false)]
        [DataRow("-=", TokenType.OperatorAssignmentSubstraction, false)]
        [DataRow("&=", TokenType.OperatorAssignmentBitwiseAnd, false)]
        [DataRow("|=", TokenType.OperatorAssignmentBitwiseOr, false)]
        [DataRow("^=", TokenType.OperatorAssignmentBitwiseXor, false)]
        [DataRow("namespace", TokenType.KeywordNamespace, false)]
        [DataRow("type", TokenType.KeywordType, false)]
        [DataRow("data", TokenType.KeywordData, false)]
        [DataRow("interface", TokenType.KeywordInterface, false)]
        [DataRow("factory", TokenType.KeywordFactory, false)]
        [DataRow("while", TokenType.KeywordWhile, false)]
        [DataRow("do", TokenType.KeywordDo, false)]
        [DataRow("if", TokenType.KeywordIf, false)]
        [DataRow("else", TokenType.KeywordElse, false)]
        [DataRow("switch", TokenType.KeywordSwitch, false)]
        [DataRow("return", TokenType.KeywordReturn, false)]
        [DataRow("throw", TokenType.KeywordThrow, false)]
        [DataRow("break", TokenType.KeywordBreak, false)]
        [DataRow("for", TokenType.KeywordFor, false)]
        [DataRow("var", TokenType.KeywordVar, false)]
        [DataRow("true", TokenType.KeywordTrue, false)]
        [DataRow("false", TokenType.KeywordFalse, false)]
        [DataRow("a", TokenType.Identifier, false)]
        [DataRow("a1", TokenType.Identifier, false)]
        [DataRow("_1a", TokenType.Identifier, false)]
        [DataRow("lorem_ipsum_1a", TokenType.Identifier, false)]
        [DataRow("_", TokenType.Identifier, false)]
        [DataRow("\"Hello\"", TokenType.StringLiteral, false)]
        [DataRow("\"Hello\\t\"", TokenType.StringLiteral, false)]
        [DataRow("\"Hello\\b\"", TokenType.StringLiteral, false)]
        [DataRow("\"Hello\\r\"", TokenType.StringLiteral, false)]
        [DataRow("\"Hello\\n\"", TokenType.StringLiteral, false)]
        [DataRow("\"Hello\\\"\"", TokenType.StringLiteral, false)]
        [DataRow("\"Hello's\"", TokenType.StringLiteral, false)]
        [DataRow("\"Hello", TokenType.ErrorUnclosedStringLiteral, false)]
        [DataRow("\"Hello\\", TokenType.ErrorUnclosedStringLiteral, false)]
        [DataRow("1234", TokenType.NumberLiteral, false)]
        [DataRow("1234.00", TokenType.NumberLiteral, false)]
        [DataRow("1_234_000.00", TokenType.NumberLiteral, false)]
        [DataRow("1.3e-27", TokenType.NumberLiteral, false)]
        [DataRow("0.000001", TokenType.NumberLiteral, false)]
        [DataRow("1234.00e", TokenType.ErrorInvalidNumberLiteral, false)]
        [DataRow("1234.00e+", TokenType.ErrorInvalidNumberLiteral, false)]
        [DataRow("1234.00e-", TokenType.ErrorInvalidNumberLiteral, false)]
        [DataRow("'2022-13-03'", TokenType.DateLiteral, false)]
        [DataRow("'2022-13-03T23:55:55.0123'", TokenType.DateLiteral, false)]
        [DataRow("'2022-13-03T23:55:55.0123+6'", TokenType.DateLiteral, false)]
        [DataRow("'2022-13-03T23:55:55.0123+6.5'", TokenType.DateLiteral, false)]
        [DataRow("'2022-13-03T23:55:55.0123Z'", TokenType.DateLiteral, false)]
        [DataRow("'T23:55:55.0123Z'", TokenType.DateLiteral, false)]
        [DataRow("'T23:55:55.0123Z", TokenType.ErrorUnclosedDateLiteral, false)]
        [DataRow("`", TokenType.UnrecognizedCharacter, false)]
        public void SingleTokenTest(string sourceCode, TokenType expectedTokenType, bool isCommentOrWhiteSpace)
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = sourceCode }
                    );
            // Act
            var noErrorsFound = lexicalAnalizer.Execute(compilerContext);
            var tokensParsed = compilerContext.TokenList;

            // Assert
            Assert.AreEqual(tokensParsed[0].IsError == false, noErrorsFound);
            Assert.AreEqual(1, tokensParsed.Count);
            Assert.AreEqual(expectedTokenType, tokensParsed[0].TokenType);
            Assert.AreEqual(sourceCode, tokensParsed[0].Value.Text);
            Assert.AreEqual(0, tokensParsed[0].Value.StartPosition);
            Assert.AreEqual(sourceCode.Length, tokensParsed[0].Value.Length);
            Assert.AreEqual(0, tokensParsed[0].ColumnNumber);
            Assert.AreEqual(0, tokensParsed[0].LineNumber);
            Assert.AreEqual(isCommentOrWhiteSpace, tokensParsed[0].IsCommentOrWhiteSpace);
        }

        [DataRow("lorem_ipsum", "lorem_ipsum")]
        [DataRow("loremIpsum", "loremIpsum")]
        [DataRow("_", "_")]
        [DataRow("a", "a")]
        [DataRow("@_hello", "_hello")]
        [DataRow("@999", "999")]
        [DataRow("@var", "var")]
        [DataRow("@namespace", "namespace")]
        [DataRow("@zzzz", "zzzz")]
        public void IdentifiersTest(string sourceCode, TokenType expectedIdentifier)
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = sourceCode }
                    );

            // Act
            var noErrorsFound = lexicalAnalizer.Execute(compilerContext);
            var tokensParsed = compilerContext.TokenList;

            // Assert
            Assert.IsTrue(noErrorsFound);
            Assert.AreEqual(1, tokensParsed.Count);
            Assert.AreEqual(TokenType.Identifier, tokensParsed[0].TokenType);
            Assert.AreEqual(expectedIdentifier, tokensParsed[0].Value.Text);
            Assert.AreEqual(0, tokensParsed[0].Value.StartPosition);
            Assert.AreEqual(sourceCode.Length, tokensParsed[0].Value.Length);
            Assert.AreEqual(0, tokensParsed[0].ColumnNumber);
            Assert.AreEqual(0, tokensParsed[0].LineNumber);

        }

        [DataTestMethod]
        [DataRow(" \n", TokenType.WhiteSpace, TokenType.NewLine)]
        [DataRow("// Lorem Ipsum \n", TokenType.SingleLineComment, TokenType.NewLine)]
        [DataRow("/* Lorem Ipsum */\n", TokenType.MultiLineComment, TokenType.NewLine)]
        [DataRow("/* Lorem Ipsum */\n", TokenType.MultiLineComment, TokenType.NewLine)]
        [DataRow("1/* Lorem \r\n Ipsum \n", TokenType.NumberLiteral, TokenType.ErrorCommentNotClosed)]
        [DataRow("1/* Lorem \r\n Ipsum", TokenType.NumberLiteral, TokenType.ErrorCommentNotClosed)]
        [DataRow(" \r\n ", TokenType.WhiteSpace, TokenType.NewLine, TokenType.WhiteSpace)]
        [DataRow("> >=", TokenType.OperatorGreaterThan, TokenType.WhiteSpace, TokenType.OperatorGreaterOrEqualsThan)]
        [DataRow(">a", TokenType.OperatorGreaterThan, TokenType.Identifier)]
        [DataRow(">= >", TokenType.OperatorGreaterOrEqualsThan, TokenType.WhiteSpace, TokenType.OperatorGreaterThan)]
        [DataRow(">=1", TokenType.OperatorGreaterOrEqualsThan, TokenType.NumberLiteral)]
        [DataRow("==1", TokenType.OperatorEquals, TokenType.NumberLiteral)]
        [DataRow("true!=false", TokenType.KeywordTrue, TokenType.OperatorNotEquals, TokenType.KeywordFalse)]
        [DataRow("1\"\n", TokenType.NumberLiteral, TokenType.ErrorUnclosedStringLiteral)]
        [DataRow("\"1\"1234.00e", TokenType.StringLiteral, TokenType.ErrorInvalidNumberLiteral)]
        [DataRow("\"1\"1234.00e+//error", TokenType.StringLiteral, TokenType.ErrorInvalidNumberLiteral, TokenType.SingleLineComment)]
        [DataRow("\"1\"1234.0099992//Hello", TokenType.StringLiteral, TokenType.NumberLiteral, TokenType.SingleLineComment)]
        [DataRow("for 1234.0099992//Hello", TokenType.KeywordFor, TokenType.WhiteSpace, TokenType.NumberLiteral, TokenType.SingleLineComment)]
        [DataRow("for(i=0;i<10;i++)", 
            TokenType.KeywordFor,
            TokenType.OpenParentesis,
            TokenType.Identifier,
            TokenType.OperatorAssignment,
            TokenType.NumberLiteral,
            TokenType.SemiColon,
            TokenType.Identifier,
            TokenType.OperatorLessThan,
            TokenType.NumberLiteral,
            TokenType.SemiColon,
            TokenType.Identifier,
            TokenType.OperatorIncrement,
            TokenType.CloseParentesis)]
        public void MultipleTokensTest(string sourceCode, params TokenType[] expectedTokenTypes)
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = sourceCode }
                    );

            // Act
            var noErrorsFound = lexicalAnalizer.Execute(compilerContext);
            var tokensParsed = compilerContext.TokenList;

            // Assert
            Assert.AreEqual(compilerContext.TokenList.All(t => t.IsError == false),  noErrorsFound);
            Assert.AreEqual(expectedTokenTypes.Length, tokensParsed.Count);
            for (int i = 0; i < expectedTokenTypes.Length; i++)
            {
                Assert.AreEqual(expectedTokenTypes[i], tokensParsed[i].TokenType);
            }
        }

        [DataTestMethod]
        [DataRow(" ", TokenType.WhiteSpace)]
        [DataRow("\n", TokenType.NewLine)]
        [DataRow("\r\n", TokenType.NewLine)]
        [DataRow("// Lorem Ipsum", TokenType.SingleLineComment)]
        [DataRow("/* Lorem \r\n Ipsum */", TokenType.MultiLineComment)]
        [DataRow("{", TokenType.OpenBrace)]
        [DataRow("}", TokenType.CloseBrace)]
        [DataRow(",", TokenType.Coma)]
        [DataRow(";", TokenType.SemiColon)]
        [DataRow(":", TokenType.Colon)]
        [DataRow("(", TokenType.OpenParentesis)]
        [DataRow(")", TokenType.CloseParentesis)]
        [DataRow("[", TokenType.OpenBraket)]
        [DataRow("]", TokenType.CloseBraket)]
        [DataRow("?", TokenType.QuestionMark)]
        [DataRow(".", TokenType.Dot)]
        [DataRow(">", TokenType.OperatorGreaterThan)]
        [DataRow("<", TokenType.OperatorLessThan)]
        [DataRow("==", TokenType.OperatorEquals)]
        [DataRow("!=", TokenType.OperatorNotEquals)]
        [DataRow(">=", TokenType.OperatorGreaterOrEqualsThan)]
        [DataRow("<=", TokenType.OperatorLessOrEqualsThan)]
        [DataRow("||", TokenType.OperatorLogicalOr)]
        [DataRow("&&", TokenType.OperatorLogicalAnd)]
        [DataRow("!", TokenType.OperatorLogicalNot)]
        [DataRow("|", TokenType.OperatorBitwiseOr)]
        [DataRow("&", TokenType.OperatorBitwiseAnd)]
        [DataRow("~", TokenType.OperatorBitwiseNot)]
        [DataRow("^", TokenType.OperatorBitwiseXor)]
        [DataRow("*", TokenType.OperatorMultiplication)]
        [DataRow("**", TokenType.OperatorExponentiation)]
        [DataRow("/", TokenType.OperatorDivision)]
        [DataRow("%", TokenType.OperatorRemainder)]
        [DataRow("+", TokenType.OperatorAddition)]
        [DataRow("-", TokenType.OperatorSubstraction)]
        [DataRow("++", TokenType.OperatorIncrement)]
        [DataRow("--", TokenType.OperatorDecrement)]
        [DataRow("?.", TokenType.OperatorNullConditional)]
        [DataRow("??", TokenType.OperatorNullCoalescing)]
        [DataRow("=", TokenType.OperatorAssignment)]
        [DataRow("*=", TokenType.OperatorAssignmentMultiply)]
        [DataRow("/=", TokenType.OperatorAssignmentDivide)]
        [DataRow("%=", TokenType.OperatorAssignmentReminder)]
        [DataRow("+=", TokenType.OperatorAssignmentAddition)]
        [DataRow("-=", TokenType.OperatorAssignmentSubstraction)]
        [DataRow("&=", TokenType.OperatorAssignmentBitwiseAnd)]
        [DataRow("|=", TokenType.OperatorAssignmentBitwiseOr)]
        [DataRow("^=", TokenType.OperatorAssignmentBitwiseXor)]
        [DataRow("namespace", TokenType.KeywordNamespace)]
        [DataRow("type", TokenType.KeywordType)]
        [DataRow("data", TokenType.KeywordData)]
        [DataRow("interface", TokenType.KeywordInterface)]
        [DataRow("factory", TokenType.KeywordFactory)]
        [DataRow("while", TokenType.KeywordWhile)]
        [DataRow("do", TokenType.KeywordDo)]
        [DataRow("if", TokenType.KeywordIf)]
        [DataRow("else", TokenType.KeywordElse)]
        [DataRow("switch", TokenType.KeywordSwitch)]
        [DataRow("return", TokenType.KeywordReturn)]
        [DataRow("throw", TokenType.KeywordThrow)]
        [DataRow("break", TokenType.KeywordBreak)]
        [DataRow("for", TokenType.KeywordFor)]
        [DataRow("var", TokenType.KeywordVar)]
        [DataRow("true", TokenType.KeywordTrue)]
        [DataRow("false", TokenType.KeywordFalse)]
        [DataRow("a", TokenType.Identifier)]
        [DataRow("a1", TokenType.Identifier)]
        [DataRow("_1a", TokenType.Identifier)]
        [DataRow("lorem_ipsum_1a", TokenType.Identifier)]
        [DataRow("_", TokenType.Identifier)]
        [DataRow("\"Hello\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\t\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\b\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\r\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\n\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\\"\"", TokenType.StringLiteral)]
        [DataRow("\"Hello's\"", TokenType.StringLiteral)]
        [DataRow("1234", TokenType.NumberLiteral)]
        [DataRow("1234.00", TokenType.NumberLiteral)]
        [DataRow("1_234_000.00", TokenType.NumberLiteral)]
        [DataRow("1.3e-27", TokenType.NumberLiteral)]
        [DataRow("0.000001", TokenType.NumberLiteral)]
        [DataRow("1234.00e", TokenType.ErrorInvalidNumberLiteral)]
        [DataRow("1234.00e+", TokenType.ErrorInvalidNumberLiteral)]
        [DataRow("1234.00e-", TokenType.ErrorInvalidNumberLiteral)]
        [DataRow("'2022-13-03'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123+6'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123+6.5'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123Z'", TokenType.DateLiteral)]
        [DataRow("'T23:55:55.0123Z'", TokenType.DateLiteral)]
        [DataRow("`", TokenType.UnrecognizedCharacter)]
        public void SingleTokenFollowedByNewLineTest(string sourceCode, TokenType expectedTokenType)
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = sourceCode + "\n" }
                    );
            // Act
            var noErrorsFound = lexicalAnalizer.Execute(compilerContext);
            var tokensParsed = compilerContext.TokenList;

            // Assert
            Assert.AreEqual(tokensParsed[0].IsError == false, noErrorsFound);
            Assert.AreEqual(2, tokensParsed.Count);
            Assert.AreEqual(expectedTokenType, tokensParsed[0].TokenType);
            Assert.AreEqual(sourceCode, tokensParsed[0].Value.Text);
            Assert.AreEqual(0, tokensParsed[0].Value.StartPosition);
            Assert.AreEqual(sourceCode.Length, tokensParsed[0].Value.Length);
            Assert.AreEqual(0, tokensParsed[0].ColumnNumber);
            Assert.AreEqual(0, tokensParsed[0].LineNumber);
            Assert.AreEqual(TokenType.NewLine, tokensParsed[1].TokenType);

        }

        [DataTestMethod]
        [DataRow("\n", TokenType.NewLine)]
        [DataRow("\r\n", TokenType.NewLine)]
        [DataRow("/* Lorem \r\n Ipsum */", TokenType.MultiLineComment)]
        [DataRow("{", TokenType.OpenBrace)]
        [DataRow("}", TokenType.CloseBrace)]
        [DataRow(",", TokenType.Coma)]
        [DataRow(";", TokenType.SemiColon)]
        [DataRow(":", TokenType.Colon)]
        [DataRow("(", TokenType.OpenParentesis)]
        [DataRow(")", TokenType.CloseParentesis)]
        [DataRow("[", TokenType.OpenBraket)]
        [DataRow("]", TokenType.CloseBraket)]
        [DataRow("?", TokenType.QuestionMark)]
        [DataRow(".", TokenType.Dot)]
        [DataRow(">", TokenType.OperatorGreaterThan)]
        [DataRow("<", TokenType.OperatorLessThan)]
        [DataRow("==", TokenType.OperatorEquals)]
        [DataRow("!=", TokenType.OperatorNotEquals)]
        [DataRow(">=", TokenType.OperatorGreaterOrEqualsThan)]
        [DataRow("<=", TokenType.OperatorLessOrEqualsThan)]
        [DataRow("||", TokenType.OperatorLogicalOr)]
        [DataRow("&&", TokenType.OperatorLogicalAnd)]
        [DataRow("!", TokenType.OperatorLogicalNot)]
        [DataRow("|", TokenType.OperatorBitwiseOr)]
        [DataRow("&", TokenType.OperatorBitwiseAnd)]
        [DataRow("~", TokenType.OperatorBitwiseNot)]
        [DataRow("^", TokenType.OperatorBitwiseXor)]
        [DataRow("*", TokenType.OperatorMultiplication)]
        [DataRow("**", TokenType.OperatorExponentiation)]
        [DataRow("/", TokenType.OperatorDivision)]
        [DataRow("%", TokenType.OperatorRemainder)]
        [DataRow("+", TokenType.OperatorAddition)]
        [DataRow("-", TokenType.OperatorSubstraction)]
        [DataRow("++", TokenType.OperatorIncrement)]
        [DataRow("--", TokenType.OperatorDecrement)]
        [DataRow("?.", TokenType.OperatorNullConditional)]
        [DataRow("??", TokenType.OperatorNullCoalescing)]
        [DataRow("=", TokenType.OperatorAssignment)]
        [DataRow("*=", TokenType.OperatorAssignmentMultiply)]
        [DataRow("/=", TokenType.OperatorAssignmentDivide)]
        [DataRow("%=", TokenType.OperatorAssignmentReminder)]
        [DataRow("+=", TokenType.OperatorAssignmentAddition)]
        [DataRow("-=", TokenType.OperatorAssignmentSubstraction)]
        [DataRow("&=", TokenType.OperatorAssignmentBitwiseAnd)]
        [DataRow("|=", TokenType.OperatorAssignmentBitwiseOr)]
        [DataRow("^=", TokenType.OperatorAssignmentBitwiseXor)]
        [DataRow("namespace", TokenType.KeywordNamespace)]
        [DataRow("type", TokenType.KeywordType)]
        [DataRow("data", TokenType.KeywordData)]
        [DataRow("interface", TokenType.KeywordInterface)]
        [DataRow("factory", TokenType.KeywordFactory)]
        [DataRow("while", TokenType.KeywordWhile)]
        [DataRow("do", TokenType.KeywordDo)]
        [DataRow("if", TokenType.KeywordIf)]
        [DataRow("else", TokenType.KeywordElse)]
        [DataRow("switch", TokenType.KeywordSwitch)]
        [DataRow("return", TokenType.KeywordReturn)]
        [DataRow("throw", TokenType.KeywordThrow)]
        [DataRow("break", TokenType.KeywordBreak)]
        [DataRow("for", TokenType.KeywordFor)]
        [DataRow("var", TokenType.KeywordVar)]
        [DataRow("true", TokenType.KeywordTrue)]
        [DataRow("false", TokenType.KeywordFalse)]
        [DataRow("a", TokenType.Identifier)]
        [DataRow("a1", TokenType.Identifier)]
        [DataRow("_1a", TokenType.Identifier)]
        [DataRow("lorem_ipsum_1a", TokenType.Identifier)]
        [DataRow("_", TokenType.Identifier)]
        [DataRow("\"Hello\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\t\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\b\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\r\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\n\"", TokenType.StringLiteral)]
        [DataRow("\"Hello\\\"\"", TokenType.StringLiteral)]
        [DataRow("\"Hello's\"", TokenType.StringLiteral)]
        [DataRow("1234", TokenType.NumberLiteral)]
        [DataRow("1234.00", TokenType.NumberLiteral)]
        [DataRow("1_234_000.00", TokenType.NumberLiteral)]
        [DataRow("1.3e-27", TokenType.NumberLiteral)]
        [DataRow("0.000001", TokenType.NumberLiteral)]
        [DataRow("1234.00e", TokenType.ErrorInvalidNumberLiteral)]
        [DataRow("1234.00e+", TokenType.ErrorInvalidNumberLiteral)]
        [DataRow("1234.00e-", TokenType.ErrorInvalidNumberLiteral)]
        [DataRow("'2022-13-03'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123+6'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123+6.5'", TokenType.DateLiteral)]
        [DataRow("'2022-13-03T23:55:55.0123Z'", TokenType.DateLiteral)]
        [DataRow("'T23:55:55.0123Z'", TokenType.DateLiteral)]
        [DataRow("`", TokenType.UnrecognizedCharacter)]
        public void SingleTokenFollowedByWhitespaceTest(string sourceCode, TokenType expectedTokenType)
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = sourceCode + " \t" }
                    );
            // Act
            var noErrorsFound = lexicalAnalizer.Execute(compilerContext);
            var tokensParsed = compilerContext.TokenList;

            // Assert
            Assert.AreEqual(tokensParsed[0].IsError == false, noErrorsFound);
            Assert.AreEqual(2, tokensParsed.Count);
            Assert.AreEqual(expectedTokenType, tokensParsed[0].TokenType);
            Assert.AreEqual(sourceCode, tokensParsed[0].Value.Text);
            Assert.AreEqual(0, tokensParsed[0].Value.StartPosition);
            Assert.AreEqual(sourceCode.Length, tokensParsed[0].Value.Length);
            Assert.AreEqual(0, tokensParsed[0].ColumnNumber);
            Assert.AreEqual(0, tokensParsed[0].LineNumber);
            Assert.AreEqual(TokenType.WhiteSpace, tokensParsed[1].TokenType);

        }
        [TestMethod]
        public void EmptyFileTest()
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = string.Empty }
                    );

            // Act
            lexicalAnalizer.Execute(compilerContext);
            var tokensParsed = compilerContext.TokenList;

            // Assert
            Assert.AreEqual(0, tokensParsed.Count);
        }       
    }
}