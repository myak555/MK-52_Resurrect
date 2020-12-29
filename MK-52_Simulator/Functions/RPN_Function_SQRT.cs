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

        public override void execute(string code)
        {
            double result = _parent.CalcStack.setImaginaryWarning(_parent.CalcStack.X.asReal);
            result = Math.Sqrt(result);
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.Replace( result);
        }
    }
}
