namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// Unit of Compilation.
    /// </summary>
    public class UnitOfCompilation
    {
        /// <summary>
        /// Getor sets the list of namespace definitions
        /// </summary>
        public List<NamespaceDefinition> NamespaceDefinitions { get; private set; } = new List<NamespaceDefinition>();
    }
}
