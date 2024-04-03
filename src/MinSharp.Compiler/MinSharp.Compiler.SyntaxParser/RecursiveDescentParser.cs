using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser
{
    internal class RecursiveDescentParser
    {
        TokenIteratorWithNoWhiteSpaces _tokenIterator;
        List<SyntaxError> _errors;

        public RecursiveDescentParser(List<Token> tokens, List<SyntaxError> errors) 
        {
            _tokenIterator = new TokenIteratorWithNoWhiteSpaces(tokens);
            _errors = errors;
        }

        public UnitOfCompilation Parse()
        {
            UnitOfCompilation result = new UnitOfCompilation();
            while ( _tokenIterator.MoveNext() )
            {
                try
                {
                    var namespaceDefinition = ParseNamespaceDefinition();
                }
                catch (SyntaxErrorException)
                {
                    throw new NotImplementedException();
                }
            }

            return result;
        }

        private NamespaceDefinition ParseNamespaceDefinition()
        {
            var result = new NamespaceDefinition();

            try
            {
                // Keyword namespace
                if (_tokenIterator.CurrentToken.TokenType != TokenType.KeywordNamespace)
                {
                    result.IsSynteticNode = true;
                    _errors.Add(
                        new SyntaxError
                        {
                            CompilationErrorCode = CompilationErrorCode.SyntaxExpectedNamespaceKeyword,
                            StartToken = _tokenIterator.CurrentToken
                        });

                    if (_tokenIterator.CurrentToken.TokenType != TokenType.Identifier)
                    {
                        _tokenIterator.MoveToNextTokenType(TokenType.OpenCurlyBracket);
                    }
                }
                else
                {
                    result.NamespaceKeywordToken = _tokenIterator.CurrentToken;
                    _tokenIterator.MoveNext();
                }

                // Doted identifier
                result.DotedIdentifier = ParseDotedIdentifier();

                // OPen curly bracket
                if (_tokenIterator.CurrentToken.TokenType != TokenType.OpenCurlyBracket)
                {
                    throw new SyntaxErrorException(CompilationErrorCode.SyntaxExpectedOpenBracket, _tokenIterator.CurrentToken);
                }
                result.OpenCurlyBracketToken = _tokenIterator.CurrentToken;
                _tokenIterator.MoveNext();

                // Placeholder until real code
                PlaceHolderForCodeInBlock();

                // Close curly bracket
                if (_tokenIterator.CurrentToken.TokenType != TokenType.CloseCurlyBracket)
                {
                    throw new SyntaxErrorException(CompilationErrorCode.SyntaxExpectedOpenBracket, _tokenIterator.CurrentToken);
                }
                result.CloseCurlyBracketToken = _tokenIterator.CurrentToken;
            }
            catch (SyntaxErrorException ex)
            {
                if (ex.SyntaxErrorCode == CompilationErrorCode.SyntaxExpectedNamespaceKeyword)
                {

                }
                throw;
            }

            return result;
        }

        private DotedIdentifier ParseDotedIdentifier()
        {
            var result = new DotedIdentifier();
            ParserDotedIdentifierIdentifier(result);
            while (_tokenIterator.CurrentToken.TokenType == TokenType.Dot)
            {
                _tokenIterator.MoveNext();
                ParserDotedIdentifierIdentifier(result);
            }
            return result;
        }

        private void ParserDotedIdentifierIdentifier(DotedIdentifier parentDotedIndentifier)
        {
            if (_tokenIterator.CurrentToken.TokenType != TokenType.Identifier)
            {
                throw new SyntaxErrorException(CompilationErrorCode.SyntaxExpectedIdentifier, _tokenIterator.CurrentToken);
            }
            parentDotedIndentifier.DotedIdentifiers.Add(
                new Identifier
                {
                    Name = _tokenIterator.CurrentToken.Value.Text,
                    IdentifierToken = _tokenIterator.CurrentToken
                });
            _tokenIterator.MoveNext();
        }

        private void PlaceHolderForCodeInBlock()
        {
            var nestedLevel = 0;
            while (_tokenIterator.CurrentToken.TokenType != TokenType.CloseCurlyBracket && nestedLevel >0)
            {
                if (_tokenIterator.CurrentToken.TokenType == TokenType.OpenCurlyBracket)
                {
                    nestedLevel++;
                }

                if (_tokenIterator.CurrentToken.TokenType == TokenType.CloseCurlyBracket)
                {
                    nestedLevel--;
                }
                if (_tokenIterator.MoveNext() == false)
                {
                    throw new SyntaxErrorException(CompilationErrorCode.SyntaxExpectedCloseCurlyBracket, _tokenIterator.CurrentToken);
                }
            }
        }
    }
}
