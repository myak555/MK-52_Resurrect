using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_FromRAD : RPN_Function
    {
        public RPN_Function_FromRAD(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "<-RAD";
            Description = "Converts radian into degrees";
        }

        public override void execute(string code)
        {
            double result = _parent.CalcStack.X.asReal;
            _parent.CalcStack.Replace(result * 180 / Math.PI);
        }
    }
}
