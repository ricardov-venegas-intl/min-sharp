namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// Unit of Compilation.
    /// </summary>
    public class UnitOfCompilation: AstNode
    {
        /// <summary>
        /// Getor sets the list of namespace definitions
        /// </summary>
        public NamespaceDefinitionList? NamespaceDefinitionsList { get; set; }
    }
}
