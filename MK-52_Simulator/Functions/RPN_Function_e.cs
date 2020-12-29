using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_e : RPN_Function
    {
        public RPN_Function_e( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "e";
            Description = "Puts E in stack";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.Push(Math.E);
        }
    }
}
