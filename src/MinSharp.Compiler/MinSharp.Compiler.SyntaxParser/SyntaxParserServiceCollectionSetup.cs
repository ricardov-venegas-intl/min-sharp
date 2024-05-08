using Microsoft.Extensions.DependencyInjection;
using MinSharp.Compiler.SyntaxParser.SyntaxElementParsers;

namespace MinSharp.Compiler.SyntaxParser
{
    public static class SyntaxParserServiceCollectionSetup
    {
        public static IServiceCollection AddServices(IServiceCollection serviceCollection)
        {
            serviceCollection.AddTransient<DotedIdentifierParser>();
            serviceCollection.AddTransient<NamespaceDefinitionParser>();
            serviceCollection.AddTransient<NamespaceDefinitionListParser>();
            serviceCollection.AddTransient<UnitOfCompilationParser>();
            serviceCollection.AddTransient<SyntaxParser>();

            return serviceCollection;
        }
    }
}
