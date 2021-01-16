using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_GOTO : RPN_Function
    {
        public RPN_Function_GOTO(MK52_Host parent)
            : base(parent)
        {
            Keyword = "GOTO ";
            Description = "Jumps to program line unconditonally";
        }

        public override bool executeCODE(string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            _parent.Program.Counter.Set(code.Substring(Keyword.Length).Trim());
            return true;
        }
    }
}
