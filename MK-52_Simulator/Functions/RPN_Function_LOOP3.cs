using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LOOP3 : RPN_Function
    {
        public RPN_Function_LOOP3(MK52_Host parent)
            : base(parent)
        {
            Keyword = "WHILE L3>0 GOTO ";
            Description = "Loops to program line by decrementing register";
        }

        public override bool executeCODE(string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            int lp = _parent.Registers.DecrementLoopRegister(3);
            if ( lp > 0)
                _parent.Program.Counter.Set(code.Substring(Keyword.Length).Trim());
            else
                _parent.Program.Counter.Increment();
            return true;
        }
    }
}
