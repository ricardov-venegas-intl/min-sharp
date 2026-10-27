using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using MinSharp.Compiler.SyntaxParser.Utils;
using NamespaceDefinition = MinSharp.Compiler.DataModels.Ast.NamespaceDefinition;

namespace MinSharp.Compiler.SyntaxParser.SyntaxElementParsers
{
    public class NamespaceDefinitionParser : IComponentParser<NamespaceDefinition>
    {
        FullyQualifiedIdentifierParser _fullyQualifiedIdentifierParser;
        TypeDefinitionListParser _typeDefinitionListParser;

        public NamespaceDefinitionParser(FullyQualifiedIdentifierParser dotedIdentifierParser, TypeDefinitionListParser typeDefinitionListParser)
        {
            _fullyQualifiedIdentifierParser = dotedIdentifierParser;
            _typeDefinitionListParser = typeDefinitionListParser;
        }

        public NamespaceDefinition Parse(SyntaxParserContext syntaxParserContext)
        {

            var result = new NamespaceDefinition();

            ParseNamespaceDefinitionNamespaceKeyword(syntaxParserContext, result);
            ParseNamespaceDefinitionIdentifier(syntaxParserContext, result);
            bool openCurlyBracketFound = ParseCurlyBracket(syntaxParserContext, result);

            // Placeholder until real code
            ParseTypeDefintionList(syntaxParserContext, result);            

            ParseCloseCurlyBracket(syntaxParserContext, result, openCurlyBracketFound);
            return result;

        }

        private static void ParseCloseCurlyBracket(SyntaxParserContext syntaxParserContext, NamespaceDefinition result, bool openCurlyBracketFound)
        {
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
        }

        private static bool ParseCurlyBracket(SyntaxParserContext syntaxParserContext, NamespaceDefinition result)
        {
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
            return openCurlyBracketFound;
        }

        private void ParseNamespaceDefinitionIdentifier(SyntaxParserContext syntaxParserContext, NamespaceDefinition result)
        {
            if (syntaxParserContext.TokenIterator.CurrentToken.TokenType == TokenType.Identifier)
            {
                try
                {
                    result.DotedIdentifier = ParserStackCheck.InvokeParser(_fullyQualifiedIdentifierParser, syntaxParserContext);
                }
                catch (Exception)
                {
                    result.IsSynteticNode = true;
                    syntaxParserContext.TokenIterator.MoveToNextTokenType(TokenType.OpenCurlyBracket);
                }
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
                syntaxParserContext.TokenIterator.MoveToNextTokenType(TokenType.OpenCurlyBracket);
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

        private void ParseTypeDefintionList(SyntaxParserContext syntaxParserContext, NamespaceDefinition result)
        {
            try
            {
                result.TypeDefinitionsList = ParserStackCheck.InvokeParser(_typeDefinitionListParser, syntaxParserContext);
            }
            catch (Exception)
            {
                // TODO: check if error recovery is needed.
                syntaxParserContext.TokenIterator.MoveToNextTokenType(TokenType.CloseCurlyBracket);
            }
        }
    }
}
