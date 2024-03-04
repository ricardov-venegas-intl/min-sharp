using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.Pipeline
{
    public class CompilationUnitContext
    {
        /// <summary>
        /// Initializes an instance of CompilationUnit
        /// </summary>
        /// <param name="compilationUnit"></param>
        /// <exception cref="ArgumentNullException"></exception>
        public CompilationUnitContext(CompilationUnitMetadata compilationUnit, CompilationUnitSourceText sourceText)
        {
            CompilationUnit = compilationUnit ?? throw new ArgumentNullException(nameof(compilationUnit));
            SourceText = sourceText ?? throw new ArgumentNullException(nameof(sourceText));
        }

        public CompilationUnitMetadata CompilationUnit { get; private init; }
        public CompilationUnitSourceText SourceText { get; set; }
        public List<Token> TokenList { get; private set; } = new List<Token>();

        public List<UnitOfCompilation> UnitOfCompilationAstList { get; set; } = new List<UnitOfCompilation>();
    }
}