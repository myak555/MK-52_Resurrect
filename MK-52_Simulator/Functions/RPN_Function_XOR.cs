using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_XOR : RPN_Function
    {
        public RPN_Function_XOR( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "XOR";
            Description = "Computes logical XOR between X and Y (as integers)";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            RPN_Value operand2 = _parent.Memory.StackValues[1];
            Int64 result = operand1.asInt ^ operand2.asInt;
            _parent.Memory.PopStack(2);
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asInt = result;
        }
    }
}
