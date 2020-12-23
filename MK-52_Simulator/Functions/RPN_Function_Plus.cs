using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Plus : RPN_Function
    {
        public RPN_Function_Plus( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "+";
            Description = "Add X and Y";
        }

        public override void execute()
        {
            _parent.Stack.Plus();
        }
    }
}
