using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LOG : RPN_Function
    {
        public RPN_Function_LOG( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "LOG";
            Description = "Computes logarithm X base Y (leaves Y in stack)";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            RPN_Value operand2 = _parent.CalcStack.Y;
            double result1 = operand1.asReal;
            if (result1 <= 0.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            double result2 = operand2.asReal;
            if (result2 <= 0.0)
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            result1 = Math.Log(result1);
            result2 = Math.Log(result2);
            if (double.IsNaN(result1) || double.IsNaN(result1) || result2 == 0.0)
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            //_parent.Memory.popStack(2); For X^Y the original MK52 leaves Y in stack
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asReal = result1/result2;
        }
    }
}
