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
            var syntaxErrorList = new List<SyntaxError>();
            var recursiveDescentParser = new RecursiveDescentParser(context.TokenList, syntaxErrorList);

            try
            {
                var unitOfCompilationAst = recursiveDescentParser.Parse();
                context.UnitOfCompilationAst = unitOfCompilationAst;
            }
            catch (SyntaxErrorException)
            {
                return false;
            }
            return true;
        }
    }
}