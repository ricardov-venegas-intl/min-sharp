namespace MinSharp.Compiler.DataModels.Ast
{
    public class AstNode
    {
        /// <summary>
        /// True if the node was generated for error recovery,
        /// false if the node was generated from source code.
        /// </summary>
        public bool IsSynteticNode = false;
    }
}
