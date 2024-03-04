namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// AST Ndode: NamespaceDefinition
    /// namespace identifier {  type_definition_list }
    /// </summary>
    public class NamespaceDefinition
    {
        /// <summary>
        /// List of types defined inside the namesapce.
        /// </summary>
        public List<TypeDefinition> TypeDefintions { get; private set; } = new List<TypeDefinition>();
    }
}
