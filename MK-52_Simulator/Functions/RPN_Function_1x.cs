using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_1x : RPN_Function
    {
        public RPN_Function_1x(MK52_Host parent)
            : base(parent)
        {
            Keyword = "1/X";
            Description = "Computes inverse of X";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            double result = operand1.asReal;
            if (result == 0.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            result = 1.0/result;
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.Replace(result);
        }
    }
}
