using MinSharp.Compiler.DataModels;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using MinSharp.Compiler.Pipeline;
using System.Collections.Generic;

namespace MinSharp.Compiler.SyntaxParser
{
    public class SyntaxParser : ICompilationUnitPipelineStep
    {
        RecursiveDescentParser _recursiveDescentParser;

        public SyntaxParser(RecursiveDescentParser recursiveDescentParser)
        {
            _recursiveDescentParser = recursiveDescentParser;
        }

        public bool Execute(CompilationUnitContext context)
        {
            // Create context
            var syntaxParserContext = new SyntaxParserContext();
            syntaxParserContext.Errors = new List<SyntaxError>();
            syntaxParserContext.TokenIterator = new TokenIteratorWithNoWhiteSpaces(context.TokenList);
            
            // Parse
            var unitOfCompilationAst = _recursiveDescentParser.Parse(syntaxParserContext);

            // Update context
            context.UnitOfCompilationAst = unitOfCompilationAst;
            context.Errors.AddRange(
                syntaxParserContext.Errors.Select(e =>
                    new CompilationError(
                        context.CompilationUnit,
                        e.StartToken.ColumnNumber,
                        e.StartToken.LineNumber,
                        e.CompilationErrorCode)));

            return syntaxParserContext.Errors.Count == 0;
        }
    }
}