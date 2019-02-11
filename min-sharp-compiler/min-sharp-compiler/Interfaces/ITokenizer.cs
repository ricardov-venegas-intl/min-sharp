using min_sharp_compiler.Types;
using System;
using System.Collections.Generic;
using System.Text;

namespace min_sharp_compiler.Interfaces
{
    /// <summary>
    /// Implements Lexical Analysis
    /// </summary>
    public interface ITokenizer
    {
        /// <summary>
        /// Parses a string into Tokens
        /// </summary>
        /// <param name="compilableUnit">Source code to compile</param>
        /// <returns>Enumeration of tokens resulting from parsing the source code</returns>
        IEnumerable<Token> Parse(string compilableUnit);
    }
}
