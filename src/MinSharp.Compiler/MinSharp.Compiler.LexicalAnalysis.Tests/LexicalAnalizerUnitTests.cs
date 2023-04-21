using Microsoft.VisualStudio.TestTools.UnitTesting;

using MinSharp.Compiler.LexicalAnalysis;
using MinSharp.Compiler.LexicalAnalysis.Model;

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
        [DataRow("var", TokenType.KeywordVar, false)]
        [DataRow("true", TokenType.KeywordTrue, false)]
        [DataRow("false", TokenType.KeywordFalse, false)]
        [DataRow("a", TokenType.Identifier, false)]
        [DataRow("a1", TokenType.Identifier, false)]
        [DataRow("_1a", TokenType.Identifier, false)]
        [DataRow("lorem_ipsum_1a", TokenType.Identifier, false)]
        [DataRow("_", TokenType.Identifier, false)]
        public void SingleTokenTest(string sourceCode, TokenType expectedTokenType, bool isCommentOrWhiteSpace)
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            // Act
            var tokensParsed = lexicalAnalizer.Parse(sourceCode).ToList();

            // Assert
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

            // Act
            var tokensParsed = lexicalAnalizer.Parse(sourceCode).ToList();

            // Assert
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
        [DataRow("/* Lorem Ipsum */\n",  TokenType.MultiLineComment, TokenType.NewLine)]
        [DataRow("/* Lorem \r\n Ipsum */\n", TokenType.MultiLineComment, TokenType.NewLine)]
        [DataRow(" \r\n ", TokenType.WhiteSpace, TokenType.NewLine, TokenType.WhiteSpace)]
        [DataRow("> >=", TokenType.OperatorGreaterThan, TokenType.WhiteSpace, TokenType.OperatorGreaterOrEqualsThan)]
        [DataRow(">= >", TokenType.OperatorGreaterOrEqualsThan, TokenType.WhiteSpace, TokenType.OperatorGreaterThan)]
        public void MultipleTokensTest(string sourceCode, params TokenType[] expectedTokenTypes)
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            // Act
            var tokensParsed = lexicalAnalizer.Parse(sourceCode).ToList();

            // Assert
            Assert.AreEqual(expectedTokenTypes.Length, tokensParsed.Count);
            for (int i =0; i < expectedTokenTypes.Length; i++)
            {
                Assert.AreEqual(expectedTokenTypes[i], tokensParsed[i].TokenType);
            }
        }
    }
}