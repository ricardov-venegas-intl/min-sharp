using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace MinSharp.Compiler.DataModels
{
    public class CompilationUnitMetadata
    {
        public CompilationUnitMetadata(string sourceFile)
        {
            this.SourceFile = sourceFile ?? throw new ArgumentNullException(nameof(sourceFile));
        }

        public string SourceFile { get; private init; }
    }
}
