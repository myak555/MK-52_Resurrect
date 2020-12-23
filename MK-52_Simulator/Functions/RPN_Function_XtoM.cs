using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_XtoM : RPN_Function
    {
        public RPN_Function_XtoM( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "X->M";
            Description = "Puts value into memory";
        }

        public override bool executeProgram(string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            code = code.Substring(Keyword.Length).Trim();
            _parent.Stack.SetMemoryFromStack(code);
            _parent.Program.Counter.Increment();
            return true;
        }
    }
}
