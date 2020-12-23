using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Prev : RPN_Function
    {
        public RPN_Function_Prev( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "Bx";
            Description = "Recovers the previous value";
        }

        public override void execute()
        {
            _parent.Stack.RecoverPreviousValue();
        }
    }
}
