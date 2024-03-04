using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.DataModels.Ast
{
    public class TypeName
    {
        public List<Identifier> Identifiers { get; set; } = new List<Identifier>();
    }
}
