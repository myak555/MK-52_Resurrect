using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_STOP : RPN_Function
    {
        public RPN_Function_STOP( MK52_Host parent):
            base(parent)
        {
            Keyword = "STOP";
            Description = "Stops a program";
        }

        public override bool executeCODE(string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            _parent.setReceiver("AUTO_N");
            return true;
        }
    }
}
