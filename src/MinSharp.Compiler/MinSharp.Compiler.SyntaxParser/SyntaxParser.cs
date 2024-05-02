using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using MinSharp.Compiler.Pipeline;
using System.Collections.Generic;

namespace MinSharp.Compiler.SyntaxParser
{
    public class SyntaxParser : ICompilationUnitPipelineStep
    {

        public SyntaxParser()
        {
        }

        public bool Execute(CompilationUnitContext context)
        {
            var syntaxErrorList = new List<SyntaxError>();
            var recursiveDescentParser = new RecursiveDescentParser(context.TokenList, syntaxErrorList);

            // Parse
            var unitOfCompilationAst = recursiveDescentParser.Parse();

            // Update context
            context.UnitOfCompilationAst = unitOfCompilationAst;
            context.Errors.AddRange(
                syntaxErrorList.Select(e =>
                    new CompilationError(
                        context.CompilationUnit,
                        e.StartToken.ColumnNumber,
                        e.StartToken.LineNumber,
                        e.CompilationErrorCode)));

            return syntaxErrorList.Count == 0;
        }
    }
}