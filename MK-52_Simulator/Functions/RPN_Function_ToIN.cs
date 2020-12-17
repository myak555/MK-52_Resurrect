using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_ToIN : RPN_Function
    {
        public RPN_Function_ToIN(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "<-IN";
            Description = "Converts inches into mm";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            double tmp = operand1.asReal;
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asReal = tmp * 25.4;
        }
    }
}
