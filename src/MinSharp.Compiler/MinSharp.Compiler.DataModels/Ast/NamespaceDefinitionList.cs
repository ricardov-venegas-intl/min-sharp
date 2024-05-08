namespace MinSharp.Compiler.DataModels.Ast
{
    public class NamespaceDefinitionList: AstNode
    {
        public List<NamespaceDefinition> NamespaceDefinitions = new List<NamespaceDefinition>();
    }
}
