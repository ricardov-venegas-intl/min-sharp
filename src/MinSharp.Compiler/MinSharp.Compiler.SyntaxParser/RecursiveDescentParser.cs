using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using MinSharp.Compiler.SyntaxParser.SyntaxElementParsers;

namespace MinSharp.Compiler.SyntaxParser
{
    public class RecursiveDescentParser
    {
        NamespaceDefinitionParser _namespaceDefinitionParser;

        public RecursiveDescentParser(NamespaceDefinitionParser namespaceDefinitionParser) 
        {
            _namespaceDefinitionParser = namespaceDefinitionParser;
        }

        public UnitOfCompilation Parse(SyntaxParserContext syntaxParserContext)
        {
            UnitOfCompilation result = new UnitOfCompilation();
            while (syntaxParserContext.TokenIterator.MoveNext() )
            {
                try
                {
                    var namespaceDefinition = _namespaceDefinitionParser.Parse(syntaxParserContext);
                }
                catch (SyntaxErrorException)
                {
                    throw new NotImplementedException();
                }
            }

            return result;
        }

       
    }
}
