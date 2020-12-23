using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Neg : RPN_Function
    {
        public RPN_Function_Neg( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "/-/";
            Description = "Negates value";
        }

        public override void execute()
        {
            _parent.Stack.StorePreviousValue();
            _parent.Stack.X.Negate();
        }
    }
}
