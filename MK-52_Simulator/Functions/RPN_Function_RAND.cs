using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_RAND : RPN_Function
    {
        public RPN_Function_RAND( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "RAND";
            Description = "Computes pseudo-random value";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            _parent.Memory.StorePreviousValue();
            _parent.Memory.PushStack(1);
            _parent.Memory.StackValues[0].asReal = _parent.myRNG.NextDouble();
        }
    }
}
