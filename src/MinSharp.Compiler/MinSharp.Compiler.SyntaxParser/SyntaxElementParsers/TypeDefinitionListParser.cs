using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser.SyntaxElementParsers
{
    public class TypeDefinitionListParser : IComponentParser<TypeDefintionList>
    {
        public TypeDefintionList Parse(SyntaxParserContext syntaxParserContext)
        {
            var result = new TypeDefintionList();

            switch (syntaxParserContext.TokenIterator.CurrentToken.TokenType)
            {
                case TokenType.KeywordType:
                    break;
                case TokenType.KeywordEnum:
                    break;
                case TokenType.KeywordData:
                    break;
                case TokenType.KeywordInterface:
                    break;
                case TokenType.KeywordFactory:
                    break;
            }

            return result;
        }
    }
}
