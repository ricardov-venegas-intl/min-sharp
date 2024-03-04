using Microsoft.VisualStudio.TestTools.UnitTesting;
using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.LexicalAnalysis;
using MinSharp.Compiler.Pipeline;
using MinSharp.Compiler.SyntaxParser;

namespace MinSharp.Compiler.SyntaxParser.Tests
{
    [TestClass]
    public class SyntaxParserUnitTests
    {
        [DataTestMethod]
        public void EmptyFileTest()
        {
            // Arrange    
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = string.Empty }
                    );

            var syntaxParser = new SyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsFound =  syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsNotNull(compilerContext.UnitOfCompilationAstList);
            Assert.AreEqual(0, compilerContext.UnitOfCompilationAstList.Count);
        }
    }
}
