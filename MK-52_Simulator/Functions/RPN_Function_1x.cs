using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_1x : RPN_Function
    {
        public RPN_Function_1x(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "1/X";
            Description = "Computes inverse of X";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            double result = operand1.asReal;
            if (result == 0.0)
            {
                _parent.setInfinityError();
                return;
            }
            result = 1.0/result;
            if (double.IsNaN(result))
            {
                _parent.setArgumentError();
                return;
            }
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asReal = result;
        }
    }
}
