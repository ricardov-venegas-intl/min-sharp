using System;
using System.Collections.Generic;
using System.Text;

namespace min_sharp_compiler.Types
{
    /// <summary>
    /// Rprsent a Token from the source code
    /// </summary>
    public class Token
    {
        /// <summary>
        /// Type of token
        /// </summary>
        public TokenType TokenType { get; set; }

        /// <summary>
        /// Token Content
        /// </summary>
        public ReadOnlyMemory<char> Value { get; set;}

        /// <summary>
        /// Absolute potition of the token in the file
        /// </summary>
        public int AbsolutePosition { get; set; }

        /// <summary>
        /// Line number of the token
        /// </summary>
        public int LineNumber { get; set; }

        /// <summary>
        /// Column number of teh token
        /// </summary>
        public int ColumnNumber { get; set; }
    }
}
