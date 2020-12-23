using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_FromIN : RPN_Function
    {
        public RPN_Function_FromIN(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "IN->";
            Description = "Converts mm into inches";
        }

        public override void execute()
        {
            double result = _parent.Stack.X.asReal;
            _parent.Stack.Replace(result/25.4);
        }
    }
}
