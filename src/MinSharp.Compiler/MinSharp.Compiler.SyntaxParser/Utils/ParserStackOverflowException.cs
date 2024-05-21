using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.SyntaxParser.Utils
{
    internal class ParserStackOverflowException: Exception
    {
        public ParserStackOverflowException(string message) : base(message) 
        { 
        }
    }
}
