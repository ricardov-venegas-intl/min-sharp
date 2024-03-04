using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// DatatypeDefinition
    /// datatype_definition
    /// data identifier { property_definition_list }
    /// </summary>
    internal class DatatypeDefinition
    {
        /// <summary>
        /// Enum Name
        /// </summary>
        public Identifier DataTypeDefinitionName { get; set; }

        /// <summary>
        /// Enum Values List
        /// </summary>
        public List<PropertyDefinition> PropertyDefinitions { get; set; } = new List<PropertyDefinition>();
    }
}
