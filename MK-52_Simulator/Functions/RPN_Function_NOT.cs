using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_NOT : RPN_Function
    {
        public RPN_Function_NOT( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "NOT";
            Description = "Computes logical AND between X and Y (as integers)";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            _parent.Memory.StackValues[0].asInt = ~operand1.asInt;
        }
    }
}
