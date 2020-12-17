using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_XpY : RPN_Function
    {
        public RPN_Function_XpY( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "X^Y";
            Description = "Computes X power Y (leaves Y in stack)";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            RPN_Value operand2 = _parent.Memory.StackValues[1];
            if (operand1.asReal == 0.0 && operand2.asReal < 0.0)
            {
                _parent.setInfinityError();
                return;
            }
            if (operand1.asReal < 0.0 && !operand2.isInt)
            {
                _parent.setArgumentError();
                return;
            }
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
                _parent.setArgumentError();
                return;
            }
            //_parent.Memory.popStack(2); // The original MK52 leaves value in stack
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asReal = result;
        }
    }
}
