using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// Enum Defintion
    /// enum_definition:
    ///   enum identifier { enum_values_list }
    /// </summary>
    internal class EnumDefinition
    {
        /// <summary>
        /// Enum Name
        /// </summary>
        public Identifier EnumDefinitionName { get; set; }

        /// <summary>
        /// Enum Values List
        /// </summary>
        public List<Identifier> EnumValuesList { get; set; } = new List<Identifier>();
    }
}
