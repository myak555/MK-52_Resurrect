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

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            double result = operand1.asReal;
            if (result <= 0.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            result = Math.Log(result);
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asReal = result;
        }
    }
}
