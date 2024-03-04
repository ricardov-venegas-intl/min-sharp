using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.DataModels.Errors
{
    public enum CompilationErrorType
    {
        Lexical,
        Syntax,
        Sematic,
        CodeGeneration
    }
}
