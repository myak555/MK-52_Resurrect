using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_10x : RPN_Function
    {
        public RPN_Function_10x(MK52_Host parent)
            : base(parent)
        {
            Keyword = "10^X";
            Description = "Computes power of 10";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            double result = operand1.asReal;
            if (result > 302.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            if (ComputeWholePower(operand1)) return;
            result = Math.Pow(10.0, result);
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.Replace(result);
        }

        private bool ComputeWholePower(RPN_Value o)
        {
            if (!o.isInt) return false;
            int pwr = Convert.ToInt32( o.asInt);
            if( pwr > 18) return false;
            double result = 1.0;
            while (pwr > 0)
            {
                result *= 10.0;
                pwr--;
            }
            while (pwr < 0)
            {
                result /= 10.0;
                pwr++;
            }
            _parent.CalcStack.Replace(result);
            return true;
        }
    }
}
