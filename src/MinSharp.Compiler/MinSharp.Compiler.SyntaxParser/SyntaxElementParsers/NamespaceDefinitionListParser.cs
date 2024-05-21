using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.SyntaxParser.Utils;

namespace MinSharp.Compiler.SyntaxParser.SyntaxElementParsers
{
    public class NamespaceDefinitionListParser : IComponentParser<NamespaceDefinitionList>
    {
        NamespaceDefinitionParser _namespaceDefinitionParser;

        public NamespaceDefinitionListParser (NamespaceDefinitionParser namespaceDefinitionParser)
        {
            _namespaceDefinitionParser = namespaceDefinitionParser;
        }

        public NamespaceDefinitionList Parse(SyntaxParserContext syntaxParserContext)
        {
            var result = new NamespaceDefinitionList();

            while (syntaxParserContext.TokenIterator.MoveNext())
            {
                var namespaceDefinition = ParserStackCheck.InvokeParser(_namespaceDefinitionParser, syntaxParserContext);
                result.NamespaceDefinitions.Add (namespaceDefinition);
            }
            return result;
        }
    }
}
