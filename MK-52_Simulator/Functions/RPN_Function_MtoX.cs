using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_MtoX : RPN_Function
    {
        public RPN_Function_MtoX( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "M->X";
            Description = "Gets value from memory";
        }

        public override void execute()
        {
            _parent.XEntry.LoadEditValue();
            _parent.Memory.StorePreviousValue();
            _parent.Memory.ClearName();
            _parent.fMode = RPN_Calculator.fMode_MX;
        }
    }
}
