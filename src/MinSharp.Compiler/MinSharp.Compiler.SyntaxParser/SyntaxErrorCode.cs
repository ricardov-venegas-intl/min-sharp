using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.SyntaxParser
{
    public enum SyntaxErrorCode
    {
        ExpectedNamespaceKeyword,
        ExpectedIdentifier,
        ExpectedOpenBracket,
        ExpectedCloseCurlyBracket,
    }
}
