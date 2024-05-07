using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser.SyntaxElementParsers
{
    public class DotedIdentifierParser
    {
        public DotedIdentifier Parse(SyntaxParserContext syntaxParserContext)
        {
            var result = new DotedIdentifier();
            ParserDotedIdentifierIdentifier(syntaxParserContext, result);
            while (syntaxParserContext.TokenIterator.CurrentToken.TokenType == TokenType.Dot)
            {
                syntaxParserContext.TokenIterator.MoveNext();
                ParserDotedIdentifierIdentifier(syntaxParserContext, result);
            }
            return result;
        }

        private void ParserDotedIdentifierIdentifier(SyntaxParserContext syntaxParserContext, DotedIdentifier parentDotedIndentifier)
        {
            if (syntaxParserContext.TokenIterator.CurrentToken.TokenType != TokenType.Identifier)
            {
                throw new SyntaxErrorException(CompilationErrorCode.SyntaxExpectedIdentifier, syntaxParserContext.TokenIterator.CurrentToken);
            }
            parentDotedIndentifier.DotedIdentifiers.Add(
                new Identifier
                {
                    Name = syntaxParserContext.TokenIterator.CurrentToken.Value.Text,
                    IdentifierToken = syntaxParserContext.TokenIterator.CurrentToken
                });
            syntaxParserContext.TokenIterator.MoveNext();
        }

    }
}
