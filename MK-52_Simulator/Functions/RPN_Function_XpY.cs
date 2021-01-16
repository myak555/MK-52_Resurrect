using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_XpY : RPN_Function
    {
        public RPN_Function_XpY( MK52_Host parent):
            base(parent)
        {
            Keyword = "X^Y";
            Description = "Computes X power Y (leaves Y in stack)";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            RPN_Value operand2 = _parent.CalcStack.Y;
            if (operand1.asReal == 0.0 && operand2.asReal < 0.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            if (operand1.asReal < 0.0 && !operand2.isInt)
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            if (ComputeWholePower(operand1, operand2)) return;
            double result = operand1.asReal;
            if (result <= 0.0 && operand2.isInt)
            {
                result = Math.Pow(-result, operand2.asReal);
                result *= -1 * (operand2.asInt % 2);
            }
            else
                result = Math.Pow(result, operand2.asReal);
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            //_parent.Memory.popStack(2); // The original MK52 leaves value in stack
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asReal = result;
        }

        private bool ComputeWholePower(RPN_Value o1, RPN_Value o2)
        {
            if (!o2.isInt) return false;
            int pwr = Convert.ToInt32(o2.asInt);
            if (pwr > 30) return false;
            double result = 1.0;
            while (pwr > 0)
            {
                result *= o1.asReal;
                pwr--;
            }
            while (pwr < 0)
            {
                result /= o1.asReal;
                pwr++;
            }
            _parent.CalcStack.Replace(result);
            return true;
        }
    }
}
