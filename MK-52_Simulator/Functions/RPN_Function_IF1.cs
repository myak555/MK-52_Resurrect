using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_IF1 : RPN_Function
    {
        public RPN_Function_IF1(MK52_Host parent)
            : base(parent)
        {
            Keyword = "IFNOT X==0 GOTO ";
            Description = "Jumps to program line with conditon";
        }

        public override bool executeCODE(string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            if (_parent.CalcStack.X.asReal != 0.0)
                _parent.Program.Counter.Set(code.Substring(Keyword.Length).Trim());
            else
                _parent.Program.Counter.Increment();
            return true;
        }
    }
}
