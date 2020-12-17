using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_MAX : RPN_Function
    {
        public RPN_Function_MAX( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "MAX";
            Description = "Leaves maximum between X and Y";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            RPN_Value operand2 = _parent.Memory.StackValues[1];
            bool result = operand1.asReal > operand2.asReal;
            _parent.Memory.StorePreviousValue();
            _parent.Memory.PopStack(result? 2: 1);
        }
    }
}
