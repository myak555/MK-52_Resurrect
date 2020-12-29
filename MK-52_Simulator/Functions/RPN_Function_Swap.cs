using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Swap: RPN_Function
    {
        public RPN_Function_Swap( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "Swap";
            Description = "Swaps X and Y";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.Swap();
        }
    }
}
