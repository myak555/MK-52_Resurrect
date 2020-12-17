using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Rotate : RPN_Function
    {
        public RPN_Function_Rotate( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "Rotate";
            Description = "Rotates stack (X to T)";
        }

        public override void execute()
        {
            RPN_Value operand1 = new RPN_Value( _parent.XEntry.LoadEditValue());
            _parent.Memory.StorePreviousValue();
            _parent.Memory.PopStack(1);
            _parent.Memory.StackValues[RPN_Memory.StackSize - 1].FromRPNValue(operand1);
        }
    }
}
