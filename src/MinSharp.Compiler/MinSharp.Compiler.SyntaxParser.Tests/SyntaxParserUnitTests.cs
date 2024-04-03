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
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(0, compilerContext.UnitOfCompilationAst.NamespaceDefinitions.Count);
        }

        [DataTestMethod]
        public void EmptySimpleNamespace()
        {
            // Arrange
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = "namespace blah {}" }
                    );

            var syntaxParser = new SyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(0, compilerContext.Errors.Count);
        }

        [DataTestMethod]
        public void EmptySimpleDottedNamespace()
        {
            // Arrange
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = "namespace blah.lorem.ipsum {}" }
                    );

            var syntaxParser = new SyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(0, compilerContext.Errors.Count);
        }

        [DataTestMethod]
        public void NamespaceMissing()
        {
            // Arrange
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = "blah {}" }
                    );

            var syntaxParser = new SyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(0, compilerContext.Errors.Count);
        }
    }
}
