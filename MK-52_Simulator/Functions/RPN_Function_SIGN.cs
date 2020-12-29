using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_SIGN : RPN_Function
    {
        public RPN_Function_SIGN( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "SIGN";
            Description = "Computes sign (-1 for negative, 1 for positive)";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            int s = 0;
            if(operand1.asReal > 0.0) s = 1; 
            if(operand1.asReal < 0.0) s = -1; 
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asInt = s;
        }
    }
}
