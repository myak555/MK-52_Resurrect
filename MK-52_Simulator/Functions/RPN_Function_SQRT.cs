using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_SQRT : RPN_Function
    {
        public RPN_Function_SQRT(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "SQRT";
            Description = "Computes square root of X";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            double result = _parent.setImaginaryWarning( operand1.asReal);
            result = Math.Sqrt(result);
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
