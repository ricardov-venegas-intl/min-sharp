using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser
{
    internal class TokenIteratorWithNoWhiteSpaces
    {
        List<Token> _tokens;
        int _currentToken = -1;
        public TokenIteratorWithNoWhiteSpaces(List<Token> tokens)
        {
            _tokens = tokens.Where(t => t.IsCommentOrWhiteSpace == false).ToList();
        }

        public bool MoveNext()
        {
            if ((_currentToken + 1) >= _tokens.Count)
            {
                return false;
            }
            _currentToken++;
            return true;
        }

        public Token CurrentToken 
        { 
            get 
            { 
                if ( _currentToken < _tokens.Count)
                {
                    return _tokens[_currentToken];
                }
                throw new IndexOutOfRangeException("There is not current token");
            } 
        }

        public bool HasNextToken
        {
            get
            {
                if (_currentToken + 1  >= _tokens.Count)
                {
                    return false;
                }
                return true;
            }
        }

        public Token NextToken
        {
            get
            {
                if (_currentToken + 1 < _tokens.Count)
                {
                    return _tokens[_currentToken +1];
                }
                throw new IndexOutOfRangeException("There is not next token");
            }
        }
    }
}
