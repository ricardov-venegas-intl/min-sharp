namespace MinSharp.Compiler.SyntaxParser
{
    public class SyntaxParserContext
    {
        public List<SyntaxError> Errors { get; set; }

        public TokenIteratorWithNoWhiteSpaces TokenIterator { get; set; }
    }
}
