using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.SyntaxParser
{
    internal class RecursiveDescentParser
    {
        TokenIteratorWithNoWhiteSpaces _tokenIterator;

        public RecursiveDescentParser(List<Token> tokens) 
        {
            _tokenIterator = new TokenIteratorWithNoWhiteSpaces(tokens);
        }

        public List<UnitOfCompilation> Parse()
        {
            List<UnitOfCompilation> result = new List<UnitOfCompilation>();
            while ( _tokenIterator.MoveNext() )
            {
                try
                {
                    if (_tokenIterator.CurrentToken.TokenType != TokenType.KeywordNamespace)
                    {
                        throw new SyntaxErrorException(SyntaxErrorCode.ExpectedNamespaceKeyword, _tokenIterator.CurrentToken);
                    }
                    throw new NotImplementedException();
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
