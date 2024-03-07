using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser
{
    internal class SyntaxErrorException : Exception
    {
        public Token ErrorStartToken { get; private set; }
        public SyntaxErrorCode SyntaxErrorCode { get; private set; }


        public SyntaxErrorException(SyntaxErrorCode syntaxErrorCode, Token errorStartToken) : base() 
        { 
            this.SyntaxErrorCode = syntaxErrorCode;
            this.ErrorStartToken = errorStartToken; 
        }
    }
}
