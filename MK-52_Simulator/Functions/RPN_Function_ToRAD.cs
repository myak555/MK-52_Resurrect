using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_ToRAD : RPN_Function
    {
        public RPN_Function_ToRAD(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "RAD->";
            Description = "Converts degrees into radian";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.Stack.X;
            double tmp = operand1.asReal;
            _parent.Stack.StorePreviousValue();
            _parent.Stack.X.asReal = tmp * Math.PI / 180.0;
        }
    }
}
