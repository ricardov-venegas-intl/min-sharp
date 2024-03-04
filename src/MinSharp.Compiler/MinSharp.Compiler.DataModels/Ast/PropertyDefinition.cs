using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// property_definition_list
    ///   dataType identifier;
    ///   dataType identifier; property_definition_list
    ///   EMPTY
    /// </summary>
    internal class PropertyDefinition
    {
        /// <summary>
        /// Property definition type
        /// </summary>
        public Identifier PropertyDefinitionType { get; set; }

        /// <summary>
        /// Property Definition Name
        /// </summary>
        public Identifier PropertyDefinitionName { get; set; }
    }
}
