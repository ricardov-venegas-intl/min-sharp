using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// function_definition
    ///     type identifier(function_parameters_list);
    /// </summary>
    internal class FunctionDefintion
    {
        /// <summary>
        /// Property definition type
        /// </summary>
        public Identifier FunctionType { get; set; }

        /// <summary>
        /// Property Definition Name
        /// </summary>
        public Identifier FunctionName { get; set; }

        // ToDO: FIX
        //public List<blah> Parameters { get; set; }
    }
}
