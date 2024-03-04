using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// interface_definition
    ///     interface identifier { function_definition_list }
    /// </summary>
    internal class InterfaceDefinition
    {
        /// <summary>
        /// Property Definition Name
        /// </summary>
        public Identifier InterfaceDefinitionName { get; set; }

        public List<FunctionDefintion> FunctionDefinitionList { get; set; }
    }
}
