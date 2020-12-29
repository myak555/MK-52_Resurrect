using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_EXP : RPN_Function
    {
        public RPN_Function_EXP( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "EXP";
            Description = "Computes exponent";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            double result = operand1.asReal;
            if (result > 695.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            result = Math.Exp( result);
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.Replace(result);
        }
    }
}
