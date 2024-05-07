using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using NamespaceDefinition = MinSharp.Compiler.DataModels.Ast.NamespaceDefinition;

namespace MinSharp.Compiler.SyntaxParser.SyntaxElementParsers
{
    public class NamespaceDefinitionParser
    {
        DotedIdentifierParser _dotedIdentifierParser;

        public NamespaceDefinitionParser(DotedIdentifierParser dotedIdentifierParser)
        {
            _dotedIdentifierParser = dotedIdentifierParser;
        }

        public NamespaceDefinition Parse(SyntaxParserContext syntaxParserContext)
        {
            var result = new NamespaceDefinition();

            ParseNamespaceDefinitionNamespaceKeyword(syntaxParserContext, result);

            ParseNamespaceDefinitionIdentifier(syntaxParserContext, result);

            bool openCurlyBracketFound = true;
            // Open curly bracket
            if (syntaxParserContext.TokenIterator.CurrentToken.TokenType != TokenType.OpenCurlyBracket)
            {
                result.IsSynteticNode = true;
                syntaxParserContext.Errors.Add(
                    new SyntaxError
                    {
                        CompilationErrorCode = CompilationErrorCode.SyntaxExpectedOpenCurlyBracket,
                        StartToken = syntaxParserContext.TokenIterator.CurrentToken
                    });
                openCurlyBracketFound = false;
            }
            result.OpenCurlyBracketToken = syntaxParserContext.TokenIterator.CurrentToken;
            syntaxParserContext.TokenIterator.MoveNext();

            // Placeholder until real code
            PlaceHolderForCodeInBlock(syntaxParserContext);

            // Close curly bracket
            if (syntaxParserContext.TokenIterator.CurrentToken.TokenType != TokenType.CloseCurlyBracket)
            {
                result.IsSynteticNode = true;
                if (openCurlyBracketFound == true)
                {
                    syntaxParserContext.Errors.Add(
                        new SyntaxError
                        {
                            CompilationErrorCode = CompilationErrorCode.SyntaxExpectedCloseCurlyBracket,
                            StartToken = syntaxParserContext.TokenIterator.CurrentToken
                        });
                }
            }
            result.CloseCurlyBracketToken = syntaxParserContext.TokenIterator.CurrentToken;

            return result;
        }

        private void ParseNamespaceDefinitionIdentifier(SyntaxParserContext syntaxParserContext, NamespaceDefinition result)
        {
            if (syntaxParserContext.TokenIterator.CurrentToken.TokenType == TokenType.Identifier)
            {
                // Doted identifier
                result.DotedIdentifier = _dotedIdentifierParser.Parse(syntaxParserContext);
            }
            else
            {
                result.IsSynteticNode = true;
                syntaxParserContext.Errors.Add(
                    new SyntaxError
                    {
                        CompilationErrorCode = CompilationErrorCode.SyntaxExpectedIdentifier,
                        StartToken = syntaxParserContext.TokenIterator.CurrentToken
                    });
            }
        }

        private void ParseNamespaceDefinitionNamespaceKeyword(SyntaxParserContext syntaxParserContext, NamespaceDefinition result)
        {
            // Keyword namespace
            if (syntaxParserContext.TokenIterator.CurrentToken.TokenType != TokenType.KeywordNamespace)
            {
                result.IsSynteticNode = true;
                syntaxParserContext.Errors.Add(
                    new SyntaxError
                    {
                        CompilationErrorCode = CompilationErrorCode.SyntaxExpectedNamespaceKeyword,
                        StartToken = syntaxParserContext.TokenIterator.CurrentToken
                    });

                if (syntaxParserContext.TokenIterator.CurrentToken.TokenType != TokenType.Identifier)
                {
                    result.DotedIdentifier = null;
                    syntaxParserContext.TokenIterator.MoveToNextTokenType(TokenType.OpenCurlyBracket);
                }
            }
            else
            {
                result.NamespaceKeywordToken = syntaxParserContext.TokenIterator.CurrentToken;
                syntaxParserContext.TokenIterator.MoveNext();
            }
        }

        private void PlaceHolderForCodeInBlock(SyntaxParserContext syntaxParserContext)
        {
            var nestedLevel = 0;
            while (syntaxParserContext.TokenIterator.CurrentToken.TokenType != TokenType.CloseCurlyBracket && nestedLevel > 0)
            {
                if (syntaxParserContext.TokenIterator.CurrentToken.TokenType == TokenType.OpenCurlyBracket)
                {
                    nestedLevel++;
                }

                if (syntaxParserContext.TokenIterator.CurrentToken.TokenType == TokenType.CloseCurlyBracket)
                {
                    nestedLevel--;
                }
                if (syntaxParserContext.TokenIterator.MoveNext() == false)
                {
                    throw new SyntaxErrorException(CompilationErrorCode.SyntaxExpectedCloseCurlyBracket, syntaxParserContext.TokenIterator.CurrentToken);
                }
            }
        }
    }
}
