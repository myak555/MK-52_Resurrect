using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Comment : RPN_Function
    {
        //
        // Comment - ignore the line
        //
        public RPN_Function_Comment(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "Comment";
            Description = "Ignores the program line";
        }

        public override bool executeProgram(string code)
        {
            code = code.Trim();
            if (!code.StartsWith("#")) return false;
            _parent.Program.Counter.Increment();
            return true;
        }
    }
}
