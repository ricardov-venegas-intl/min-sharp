using System;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using min_sharp_compiler.Tokenizer;
using min_sharp_compiler.Interfaces;
using min_sharp_compiler.Types;

namespace TokenizerTests
{
    /// <summary>
    /// Tokenizer unit tests
    /// </summary>
    [TestClass]
    public class TokenizerUnitTests
    {
        /// <summary>
        /// Test a CRLF
        /// </summary>
        [TestMethod]
        public void CarriageReturnLineFeed()
        {
            ITokenizer tokenizer = new Tokenizer();
            var tokens =  tokenizer.Parse("\r\n").ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.LineTerminator, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, "\r\n", StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Line Feed Only
        /// </summary>
        [TestMethod]
        public void LineFeed()
        {
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse("\n").ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.LineTerminator, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, "\n", StringComparison.Ordinal));
        }

        /// <summary>
        /// Tests 2 lines
        /// </summary>
        [TestMethod]
        public void TwoLines()
        {
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse("\n\r\n").ToArray();
            Assert.AreEqual(2, tokens.Length);

            Assert.AreEqual(TokenType.LineTerminator, tokens[0].TokenType);
            Assert.AreEqual(TokenType.LineTerminator, tokens[1].TokenType);

            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.AreEqual(1, tokens[1].AbsolutePosition);
            Assert.AreEqual(1, tokens[1].ColumnNumber);
            Assert.AreEqual(2, tokens[1].LineNumber);

            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, "\n", StringComparison.Ordinal));
            Assert.IsTrue(MemoryExtensions.Equals(tokens[1].Value.Span, "\r\n", StringComparison.Ordinal));
        }

        /// <summary>
        /// Test a single white space
        /// </summary>
        [TestMethod]
        public void SingleWhiteSpace()
        {
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(" ").ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.WhileSpace, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, " ", StringComparison.Ordinal));
        }

        /// <summary>
        /// Test a single white space
        /// </summary>
        [TestMethod]
        public void MultipleWhiteSpacesAndTabs()
        {
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse("  \t  \t").ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.WhileSpace, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, "  \t  \t", StringComparison.Ordinal));
        }

        /// <summary>
        /// Test a single white space
        /// </summary>
        [TestMethod]
        public void SingleLineComment()
        {
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse("// This is a Single Line Coment").ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.Comment, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, "// This is a Single Line Coment", StringComparison.Ordinal));
        }

    }
}
