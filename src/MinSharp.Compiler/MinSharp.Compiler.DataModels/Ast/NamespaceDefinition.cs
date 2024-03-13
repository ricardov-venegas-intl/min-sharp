using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// AST Node: NamespaceDefinition
    /// namespace identifier {  type_definition_list }
    /// </summary>
    public class NamespaceDefinition : AstNode
    {
        /// <summary>
        /// Gets or set the Namespace Keyword Token.
        /// </summary>
        public Token? NamespaceKeywordToken { get; set; }

        /// <summary>
        /// Gets or sets the Open Bracket Token
        /// </summary>
        public Token? OpenCurlyBracketToken { get; set; }

        /// <summary>
        /// Gets or sets the Close Bracket Token
        /// </summary>
        public Token? CloseCurlyBracketToken { get; set; }

        /// <summary>
        /// Gets or set the DotedIdentifier.
        /// </summary>
        public DotedIdentifier? DotedIdentifier { get; set; }

        /// <summary>
        /// Gets or set the list of types defined inside the namespace.
        /// </summary>
        public List<TypeDefinition>? TypeDefinitions { get; private set; } = new List<TypeDefinition>();
    }
}
