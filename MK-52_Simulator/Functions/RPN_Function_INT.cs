using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_INT : RPN_Function
    {
        public RPN_Function_INT( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "[X]";
            Description = "Computes whole part";
        }

        public override void execute(string code)
        {
            double result = _parent.CalcStack.X.asReal;
            _parent.CalcStack.Replace(Math.Truncate(result));
        }
    }
}
