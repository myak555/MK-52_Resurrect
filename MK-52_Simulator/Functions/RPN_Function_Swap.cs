using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Swap: RPN_Function
    {
        public RPN_Function_Swap( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "Swap";
            Description = "Swaps X and Y";
        }

        public override void execute()
        {
            RPN_Value operand0 = new RPN_Value(_parent.XEntry.LoadEditValue());
            RPN_Value operand1 = new RPN_Value(_parent.Memory.StackValues[1]);
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[1].FromRPNValue(operand0);
            _parent.Memory.StackValues[0].FromRPNValue(operand1);
        }
    }
}
