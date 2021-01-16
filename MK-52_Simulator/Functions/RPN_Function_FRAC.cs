using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_FRAC : RPN_Function
    {
        public RPN_Function_FRAC( MK52_Host parent):
            base(parent)
        {
            Keyword = "{X}";
            Description = "Computes fractional part";
        }

        public override void execute(string code)
        {
            double result = _parent.CalcStack.X.asReal;
            result -= Math.Truncate(result);
            _parent.CalcStack.Replace(result);
        }
    }
}
