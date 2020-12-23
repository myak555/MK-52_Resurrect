using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_ToIN : RPN_Function
    {
        public RPN_Function_ToIN(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "<-IN";
            Description = "Converts inches into mm";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.Stack.X;
            double tmp = operand1.asReal;
            _parent.Stack.StorePreviousValue();
            _parent.Stack.X.asReal = tmp * 25.4;
        }
    }
}
