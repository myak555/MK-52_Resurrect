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

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            double result = operand1.asReal;
            result = Math.Truncate(result);
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asReal = result;
        }
    }
}
