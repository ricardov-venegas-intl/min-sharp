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
            var source = "\r\n";
            ITokenizer tokenizer = new Tokenizer();
            var tokens =  tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.LineTerminator, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Line Feed Only
        /// </summary>
        [TestMethod]
        public void LineFeed()
        {
            var source = "\n";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.LineTerminator, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
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
            var source = " ";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.WhiteSpace, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test a single white space
        /// </summary>
        [TestMethod]
        public void MultipleWhiteSpacesAndTabs()
        {
            var source = "  \t  \t";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.WhiteSpace, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test a single white space
        /// </summary>
        [TestMethod]
        public void SingleLineComment()
        {
            var source = "// This is a Single Line Comment";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.Comment, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }


        /// <summary>
        /// Test a single white space
        /// </summary>
        [TestMethod]
        public void StringLiteral()
        {
            var source = "\"Hello World\"";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.StringLiteral, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test a single white space
        /// </summary>
        [TestMethod]
        public void StringLiteralWithEscape()
        {
            var source = "\"Hello \\ \\nWorld\"";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.StringLiteral, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Keyword async
        /// </summary>
        [TestMethod]
        public void KeywordAsync()
        {
            var source = "async";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.KeywordAsync, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Keyword await
        /// </summary>
        [TestMethod]
        public void KeywordAwait()
        {
            var source = "await";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.KeywordAwait, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Keyword import
        /// </summary>
        [TestMethod]
        public void KeywordImport()
        {
            var source = "import";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.KeywordImport, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Keyword import
        /// </summary>
        [TestMethod]
        public void KeywordNamespace()
        {
            var source = "namespace";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.KeywordNamespace, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }


        /// <summary>
        /// Test Keyword import
        /// </summary>
        [TestMethod]
        public void KeywordUsing()
        {
            var source = "using";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.KeywordUsing, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Block Start
        /// </summary>
        [TestMethod]
        public void BlockStart()
        {
            var source = "{";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.BlockStart, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Block End
        /// </summary>
        [TestMethod]
        public void BlockEnd()
        {
            var source = "}";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.BlockEnd, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Parentesis Start
        /// </summary>
        [TestMethod]
        public void ParentesisStart()
        {
            var source = "(";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.ParentesisStart, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Parentesis End
        /// </summary>
        [TestMethod]
        public void ParentesisEnd()
        {
            var source = ")";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.ParentesisEnd, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Colon
        /// </summary>
        [TestMethod]
        public void Colon()
        {
            var source = ":";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.Colon, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Colon
        /// </summary>
        [TestMethod]
        public void SemiColon()
        {
            var source = ";";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.SemiColon, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Operator Lambda Declaration
        /// </summary>
        [TestMethod]
        public void OperatorLambdaDeclaration()
        {
            var source = "=>";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.OperatorLambdaDeclaration, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Operator Assign
        /// </summary>
        [TestMethod]
        public void OperatorAssign()
        {
            var source = "=";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source).ToArray();
            Assert.AreEqual(1, tokens.Length);
            Assert.AreEqual(TokenType.OperatorAssign, tokens[0].TokenType);
            Assert.AreEqual(0, tokens[0].AbsolutePosition);
            Assert.AreEqual(1, tokens[0].ColumnNumber);
            Assert.AreEqual(1, tokens[0].LineNumber);
            Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }

        /// <summary>
        /// Test Keyword import
        /// </summary>
        [TestMethod]
        public void HelloWorld()
        {
            TokenType[] expectedTokens = {
                TokenType.KeywordUsing,
                TokenType.Identifier,
                TokenType.SemiColon,
                TokenType.KeywordImport,
                TokenType.Identifier,
                TokenType.SemiColon,
                TokenType.KeywordNamespace,
                TokenType.Identifier,
                TokenType.BlockStart,
                TokenType.KeywordPublic,
                TokenType.KeywordModule,
                TokenType.Identifier,
                TokenType.Colon,
                TokenType.Identifier,
                TokenType.BlockStart,
                TokenType.KeywordUsing,
                TokenType.Identifier,
                TokenType.Identifier,
                TokenType.SemiColon,
                TokenType.Identifier,
                TokenType.OperatorAssign,
                TokenType.KeywordAsync,
                TokenType.ParentesisStart,
                TokenType.ParentesisEnd,
                TokenType.OperatorLambdaDeclaration,
                TokenType.BlockStart,
                TokenType.KeywordAwait,
                TokenType.Identifier,
                TokenType.ParentesisStart,
                TokenType.StringLiteral,
                TokenType.ParentesisEnd,
                TokenType.SemiColon,
                TokenType.BlockEnd,
                TokenType.BlockEnd,
                TokenType.BlockEnd
            };

            var source = @"
// This is a work in progress sample
using System;
import System.Console; 
namespace HelloWorldSample 
{
/// <summary>
/// Implements a simple Console Service
/// </summary>
public module HelloWorld: IConsoleApp 
{
    using IConsole console; // Automatic IoC
    IConsoleApp.StartUp = async () => // modules only receive Data structures in calls
    {
        await console.WriteLine(""Hello World!"");
    }
}
}";
            ITokenizer tokenizer = new Tokenizer();
            var tokens = tokenizer.Parse(source)
                            .Where(t => t.TokenType != TokenType.WhiteSpace 
                                    && t.TokenType != TokenType.LineTerminator
                                    && t.TokenType != TokenType.Comment).ToArray();

            for (int tokenIndex=0; tokenIndex < expectedTokens.Length; tokenIndex++)
            {
                Console.WriteLine("tokenIndex:{0}, expectedTokens:{1}, actualTokens:{2}", tokenIndex, expectedTokens[tokenIndex], tokens[tokenIndex].TokenType);
                Assert.AreEqual(expectedTokens[tokenIndex], tokens[tokenIndex].TokenType);
            }
            //Assert.AreEqual(1, tokens.Length);
            //Assert.AreEqual(TokenType.KeywordUsing, tokens[0].TokenType);
            //Assert.AreEqual(0, tokens[0].AbsolutePosition);
            //Assert.AreEqual(1, tokens[0].ColumnNumber);
            //Assert.AreEqual(1, tokens[0].LineNumber);
            //Assert.IsTrue(MemoryExtensions.Equals(tokens[0].Value.Span, source, StringComparison.Ordinal));
        }
    }
}
