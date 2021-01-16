using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_RAD : RPN_Function
    {
        public RPN_Function_RAD( MK52_Host parent):
            base(parent)
        {
            Keyword = "RAD";
            Description = "Set trig mode to Radians";
        }

        public override void execute(string code)
        {
            _parent.dMode = MK52_Host.dMode_Radian; 
        }
    }
}
