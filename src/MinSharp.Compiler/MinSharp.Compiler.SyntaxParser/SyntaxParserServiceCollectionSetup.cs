using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
            serviceCollection.AddTransient<RecursiveDescentParser>();
            serviceCollection.AddTransient<SyntaxParser>();

            return serviceCollection;
        }
    }
}
