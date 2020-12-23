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
            double result = _parent.Stack.setImaginaryWarning(_parent.Stack.X.asReal);
            result = Math.Sqrt(result);
            if (double.IsNaN(result))
            {
                _parent.Stack.setArgumentError();
                return;
            }
            _parent.Stack.Replace( result);
        }
    }
}
