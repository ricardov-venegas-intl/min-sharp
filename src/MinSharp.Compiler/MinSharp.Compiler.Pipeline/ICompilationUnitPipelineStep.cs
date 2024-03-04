namespace MinSharp.Compiler.Pipeline
{
    /// <summary>
    /// Compilation Unit Pipeline Step.
    /// </summary>
    public interface ICompilationUnitPipelineStep
    {
        /// <summary>
        /// Executes a Step
        /// </summary>
        /// <param name="context">Current Compilation </param>
        /// <returns>True if the compilation can continue. False to abort the following steps.</returns>
        bool Execute(CompilationUnitContext context);
    }
}
