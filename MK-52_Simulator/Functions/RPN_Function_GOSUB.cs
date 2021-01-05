using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_GOSUB : RPN_Function
    {
        public RPN_Function_GOSUB(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "GOSUB ";
            Description = "Calls a subroutine at given address";
            containsAddress = true;
        }

        public override bool executeCODE(string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            int returnAddress = _parent.Program.Counter.V;
            _parent.CallStack.Push(returnAddress); 
            _parent.Program.Counter.Set(code.Substring(Keyword.Length).Trim());
            return true;
        }
    }
}
