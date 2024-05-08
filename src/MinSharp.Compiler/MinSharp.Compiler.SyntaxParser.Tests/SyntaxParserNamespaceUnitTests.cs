using Microsoft.Extensions.DependencyInjection;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.LexicalAnalysis;
using MinSharp.Compiler.Pipeline;
using MinSharp.Compiler.SyntaxParser;
using MinSharp.Compiler.SyntaxParser.SyntaxElementParsers;
using Microsoft.Extensions.DependencyInjection;

namespace MinSharp.Compiler.SyntaxParser.Tests
{
    [TestClass]
    public class SyntaxParserNamespaceUnitTests
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

            var syntaxParser = BuildSyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsNotFound =  syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsTrue( errorsNotFound );
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

            var syntaxParser = BuildSyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsNotFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsTrue(errorsNotFound);
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

            var syntaxParser = BuildSyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsNotFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsTrue(errorsNotFound);
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(0, compilerContext.Errors.Count);
        }

        [DataTestMethod]
        public void NamespaceKeywordMissing()
        {
            // Arrange
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = "blah {}" }
                    );

            var syntaxParser = BuildSyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsNotFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsFalse(errorsNotFound);
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(1, compilerContext.Errors.Count);
            Assert.AreEqual(CompilationErrorCode.SyntaxExpectedNamespaceKeyword, compilerContext.Errors[0].ErrorCode);
        }

        [DataTestMethod]
        public void IdentifierKeywordMissing()
        {
            // Arrange
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = "namespace {}" }
                    );

            var syntaxParser = BuildSyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsNotFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsFalse(errorsNotFound);
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(1, compilerContext.Errors.Count);
            Assert.AreEqual(CompilationErrorCode.SyntaxExpectedIdentifier, compilerContext.Errors[0].ErrorCode);
        }

        [DataTestMethod]
        public void BlockMissingMissing()
        {
            // Arrange
            var lexicalAnalizer = new LexicalAnalizer();

            var compilerContext = new CompilationUnitContext(
                new DataModels.CompilationUnitMetadata("sourcefile.ms"),
                    new CompilationUnitSourceText { Text = "namespace blah;" }
                    );

            var syntaxParser = BuildSyntaxParser();
            lexicalAnalizer.Execute(compilerContext);

            // Act
            var errorsNotFound = syntaxParser.Execute(compilerContext);

            // Assert
            Assert.IsFalse(errorsNotFound);
            Assert.IsNotNull(compilerContext.UnitOfCompilationAst);
            Assert.AreEqual(1, compilerContext.Errors.Count);
            Assert.AreEqual(CompilationErrorCode.SyntaxExpectedOpenCurlyBracket, compilerContext.Errors[0].ErrorCode);
        }

        private ICompilationUnitPipelineStep BuildSyntaxParser()
        {
            
            var serviceCollection = new ServiceCollection();
            SyntaxParserServiceCollectionSetup.AddServices(serviceCollection);
            var serviceProvider = serviceCollection.BuildServiceProvider();

            var result = serviceProvider.GetService<SyntaxParser>();
            return result;
        }
    }
}

