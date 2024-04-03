using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.Errors;
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

        /// <summary>
        /// Gets CompilationUnit
        /// </summary>
        public CompilationUnitMetadata CompilationUnit { get; private init; }

        /// <summary>
        /// Gets teh source text
        /// </summary>
        public CompilationUnitSourceText SourceText { get; private init; }

        /// <summary>
        /// Gets the list of tokens.
        /// </summary>
        public List<Token> TokenList { get; private init; } = new List<Token>();

        /// <summary>
        /// Gets the list od errors.
        /// </summary>
        public List<CompilationError> Errors { get; private set; } = new List<CompilationError>();

        /// <summary>
        /// Gets the Unit Of Compilation Ast.
        /// </summary>
        public UnitOfCompilation? UnitOfCompilationAst { get; set; } = null;
    }
}