using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser
{
    /// <summary>
    /// Syntax Error Exception
    /// </summary>
    internal class SyntaxErrorException : Exception
    {
        /// <summary>
        /// Gets the Error Start Token
        /// </summary>
        public Token ErrorStartToken { get; private set; }

        /// <summary>
        /// Gets the Syntax Error Code
        /// </summary>
        public CompilationErrorCode SyntaxErrorCode { get; private set; }

        /// <summary>
        /// Initializes an instance of Syntax Error Exception.
        /// </summary>
        /// <param name="syntaxErrorCode">Compilation Error Code.</param>
        /// <param name="errorStartToken">Error Start Token.</param>
        public SyntaxErrorException(CompilationErrorCode syntaxErrorCode, Token errorStartToken) : base() 
        { 
            this.SyntaxErrorCode = syntaxErrorCode;
            this.ErrorStartToken = errorStartToken; 
        }
    }
}
