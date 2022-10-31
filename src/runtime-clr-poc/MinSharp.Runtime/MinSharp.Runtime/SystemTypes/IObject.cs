using System;
using System.Collections.Generic;
using System.Text;

namespace MinSharp.Runtime.SystemTypes
{
    public delegate IObject GetInterface(out IObject exception, string interfaceName);
    public interface IObject
    {
        GetInterface GetInterface { get; }
    }
}
