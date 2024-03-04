namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// Type Macro Definition
    /// type_macro_definition: 
    ///   type identifier: type_list;
    /// </summary>
    public class TypeMacroDefinition : TypeDefinition
    {
        /// <summary>
        /// DataTypeDefintionName
        /// </summary>
        public Identifier Identifier;

        // LIst of Types
        public List<TypeName> Types = new List<TypeName>();

    }
}
