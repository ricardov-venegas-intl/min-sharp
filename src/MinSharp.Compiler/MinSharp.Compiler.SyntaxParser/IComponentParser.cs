using MinSharp.Compiler.DataModels.Ast;

namespace MinSharp.Compiler.SyntaxParser
{
    public interface IComponentParser<T> where T : AstNode
    {
        public T Parse(SyntaxParserContext syntaxParserContext);
    }
}
