using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LG : RPN_Function
    {
        public RPN_Function_LG(MK52_Host parent)
            : base(parent)
        {
            Keyword = "LG";
            Description = "Computes logarithm base 10";
        }

        public override void execute(string code)
        {
            double result = _parent.CalcStack.X.asReal;
            if (result <= 0.0)
            {
                _parent.CalcStack.setInfinityError();
                return;
            }
            result = Math.Log10(result);
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.Replace(result);
        }
    }
}
