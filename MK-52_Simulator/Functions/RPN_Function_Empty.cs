using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Empty : RPN_Function
    {
        //
        // Tries to process a generic number into stack X value
        //
        public RPN_Function_Empty(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "Empty";
            Description = "Omits an empty program line";
        }

        public override bool executeProgram(string code)
        {
            if (code.Length > 0) return false;
            _parent.Program.Counter.Increment();
            return true;
        }
    }
}
