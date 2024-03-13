using MinSharp.Compiler.DataModels.LexicalAnalisys;

namespace MinSharp.Compiler.DataModels.Ast
{
    /// <summary>
    /// Represents a Doted Identifier node.
    /// </summary>
    public class DotedIdentifier: AstNode
    {
        /// <summary>
        /// Gets or set the doten Identifier tokens
        /// </summary>
        public List<Token> DotedIdentifierTokens { get; set; } = new List<Token> ();

        /// <summary>
        /// Gets or set the doted Identifiers node list.
        /// </summary>
        public List<Identifier> DotedIdentifiers = new List<Identifier> ();
    }
}
