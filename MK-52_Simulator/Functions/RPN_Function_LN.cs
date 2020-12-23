using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LN : RPN_Function
    {
        public RPN_Function_LN(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "LN";
            Description = "Computes natural logarithm";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.Stack.X;
            double result = operand1.asReal;
            if (result <= 0.0)
            {
                _parent.Stack.setInfinityError();
                return;
            }
            result = Math.Log(result);
            if (double.IsNaN(result))
            {
                _parent.Stack.setArgumentError();
                return;
            }
            _parent.Stack.StorePreviousValue();
            _parent.Stack.X.asReal = result;
        }
    }
}
