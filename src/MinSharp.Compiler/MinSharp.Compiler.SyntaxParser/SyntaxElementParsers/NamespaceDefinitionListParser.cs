using MinSharp.Compiler.DataModels.Ast;

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
                var namespaceDefinition = _namespaceDefinitionParser.Parse(syntaxParserContext);
                result.NamespaceDefinitions.Add (namespaceDefinition);
            }
            return result;
        }
    }
}
