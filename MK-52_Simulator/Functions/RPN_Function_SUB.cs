using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_SUB : RPN_Function
    {
        public RPN_Function_SUB( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "SUB";
            Description = "Calls a subroutine";
        }

        public override void execute()
        {
            return;
        }
    }
}
