using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser
{
    internal class TokenIteratorWithNoWhiteSpaces
    {
        Token _endOfFileToken;

        List<Token> _tokens;
        int _currentToken = -1;
        public TokenIteratorWithNoWhiteSpaces(List<Token> tokens)
        {
            _tokens = tokens.Where(t => t.IsCommentOrWhiteSpace == false).ToList();
            if (_tokens.Count > 0)
            {
                _endOfFileToken = new Token
                {
                    TokenType = TokenType.EndOfFile,
                    IsCommentOrWhiteSpace = true,
                    Value = new SourceTextSpan
                    {
                        Length = 0,
                        SourceText = tokens.Last().Value.SourceText,
                        StartPosition = tokens.Last().Value.StartPosition,
                    },
                    LineNumber = tokens.Last().LineNumber,
                    ColumnNumber = tokens.Last().ColumnNumber + 1,
                };
            }
            else
            {
                _endOfFileToken = new Token
                {
                    TokenType = TokenType.EndOfFile,
                    IsCommentOrWhiteSpace = true,
                    Value = SourceTextSpan.Empty,
                    LineNumber = 0,
                    ColumnNumber = 0,
                };
            }
        }

        public bool MoveNext()
        {
            if ((_currentToken + 1) >= _tokens.Count)
            {
                _currentToken++;
                return false;
            }
            _currentToken++;
            return true;
        }

        public bool MoveToNextTokenType(TokenType tokenType)
        {
            if ((_currentToken + 1) >= _tokens.Count)
            {
                _currentToken++;
                return false;
            }
            while ((_currentToken + 1) < _tokens.Count 
                && _tokens[_currentToken].TokenType != tokenType)
            {
                _currentToken++;
            }

            if ((_currentToken + 1) >= _tokens.Count)
            {
                _currentToken++;
                return false;
            }
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
                return _endOfFileToken;
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
                return _endOfFileToken;
            }
        }
    }
}
