using MinSharp.Compiler.DataModels;
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
            var recursiveDescentParser = new RecursiveDescentParser(context.TokenList);

            try
            {
                var unitOfCompilationAstList = recursiveDescentParser.Parse();
                context.UnitOfCompilationAstList.Clear();
                context.UnitOfCompilationAstList.AddRange(unitOfCompilationAstList);
            }
            catch (SyntaxErrorException)
            {
                return false;
            }
            return true;
        }
    }
}