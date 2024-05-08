using MinSharp.Compiler.DataModels.Ast;

namespace MinSharp.Compiler.SyntaxParser.SyntaxElementParsers
{
    public class UnitOfCompilationParser : IComponentParser<UnitOfCompilation>
    {
        NamespaceDefinitionListParser _namespaceDefinitionListParser;

        public UnitOfCompilationParser(NamespaceDefinitionListParser namespaceDefinitionListParser)
        {
            _namespaceDefinitionListParser = namespaceDefinitionListParser;
        }

        public UnitOfCompilation Parse(SyntaxParserContext syntaxParserContext)
        {
            UnitOfCompilation result = new UnitOfCompilation();

            result.NamespaceDefinitionsList = _namespaceDefinitionListParser.Parse(syntaxParserContext);

            return result;
        }
    }
}
