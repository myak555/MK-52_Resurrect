using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_x2 : RPN_Function
    {
        public RPN_Function_x2(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "X^2";
            Description = "Computes X squared";
        }

        public override void execute()
        {
            _parent.Stack.Multiply();
        }
    }
}
