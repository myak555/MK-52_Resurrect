using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_pi : RPN_Function
    {
        public RPN_Function_pi( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "pi";
            Description = "Puts PI in stack";
        }

        public override void execute()
        {
            _parent.Stack.Push(Math.PI);
        }
    }
}
