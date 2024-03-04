using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using MinSharp.Compiler.Pipeline;
using System.Collections.Generic;

namespace MinSharp.Compiler.SyntaxParser
{
    public class SyntaxParser : ICompilationUnitPipelineStep
    {
        private RecursiveDescentParser recursiveDescentParser;

        public SyntaxParser()
        {
            this.recursiveDescentParser = new RecursiveDescentParser();
        }

        public bool Execute(CompilationUnitContext context)
        {
            try
            {
                var unitOfCompilationAstList = recursiveDescentParser.Parse(context.TokenList);
                context.UnitOfCompilationAstList.Clear();
                context.UnitOfCompilationAstList.AddRange(unitOfCompilationAstList);
            }
            catch (Exception)
            {
                return false;
            }
            return true;
        }
    }
}