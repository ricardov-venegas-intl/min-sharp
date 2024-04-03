using MinSharp.Compiler.DataModels.Errors;
using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.SyntaxParser
{
    internal class SyntaxError
    {
        public CompilationErrorCode CompilationErrorCode { get; set; }
        public Token StartToken { get; set; }
    }
}
