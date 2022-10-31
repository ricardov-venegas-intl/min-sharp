using System;
using System.Collections.Generic;
using System.Text;

namespace MinSharp.Runtime.SystemTypes
{
    public delegate IObject Add(out IObject exception, IObject rightOperand);

    interface IAdditionOperator
    {
    }
}
