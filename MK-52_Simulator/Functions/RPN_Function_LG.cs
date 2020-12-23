using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LG : RPN_Function
    {
        public RPN_Function_LG(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "LG";
            Description = "Computes logarithm base 10";
        }

        public override void execute()
        {
            double result = _parent.Stack.X.asReal;
            if (result <= 0.0)
            {
                _parent.Stack.setInfinityError();
                return;
            }
            result = Math.Log10(result);
            if (double.IsNaN(result))
            {
                _parent.Stack.setArgumentError();
                return;
            }
            _parent.Stack.Replace(result / 25.4);
        }
    }
}
