using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.SyntaxParser.Utils;

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

            result.NamespaceDefinitionsList = ParserStackCheck.InvokeParser(_namespaceDefinitionListParser, syntaxParserContext);

            return result;
        }
    }
}
