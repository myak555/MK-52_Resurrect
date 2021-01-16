using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_NOP : RPN_Function
    {
        public RPN_Function_NOP( MK52_Host parent):
            base(parent)
        {
            Keyword = "NOP";
            Description = "Does nothing";
        }

        public override void execute(string code)
        {
        }
    }
}
