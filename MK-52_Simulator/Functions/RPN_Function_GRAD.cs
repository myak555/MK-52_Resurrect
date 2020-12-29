using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_GRAD : RPN_Function
    {
        public RPN_Function_GRAD( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "GRAD";
            Description = "Set trig mode to Grads";
        }

        public override void execute(string code)
        {
            _parent.dMode = RPN_Calculator.dMode_Gradian; 
        }
    }
}
