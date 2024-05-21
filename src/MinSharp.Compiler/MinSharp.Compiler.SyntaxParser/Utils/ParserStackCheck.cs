using MinSharp.Compiler.DataModels.Ast;
using MinSharp.Compiler.DataModels.LexicalAnalisys;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace MinSharp.Compiler.SyntaxParser.Utils
{
    internal static class ParserStackCheck
    {
        private const int MaxAllowedParserDepth = 256;

        public static T InvokeParser<T>(IComponentParser<T> componentParser, SyntaxParserContext syntaxParserContext) where T : AstNode
        {
            if (syntaxParserContext.CurrentParserStackDepth > MaxAllowedParserDepth)
            {
                throw new ParserStackOverflowException($"Parser Stack Overflow, Max Allowed Parser Depth: {MaxAllowedParserDepth}");
            }

            try
            {
                syntaxParserContext.CurrentParserStackDepth++;
                var result = componentParser.Parse(syntaxParserContext);
                return result;
            }
            finally
            {
                syntaxParserContext.CurrentParserStackDepth--;
            }
        }
    }
}
