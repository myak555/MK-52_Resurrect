using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Empty : RPN_Function
    {
        //
        // Ignore an empty line
        //
        public RPN_Function_Empty(MK52_Host parent)
            : base(parent)
        {
            Keyword = "Empty";
            Description = "Ignores an empty line";
        }

        public override bool executeCODE(string code)
        {
            if (code.Length != 0) return false;
            _parent.Program.Counter.Increment();
            return true;
        }
    }
}
