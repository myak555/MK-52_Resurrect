using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LblT : RPN_Function
    {
        public RPN_Function_LblT( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "LT>";
            Description = "Puts value into T Label";
        }

        public override bool executeProgram(string code)
        {
            if (!code.StartsWith(Keyword)) return false;
            code = code.Substring(Keyword.Length).Trim();
            _parent.Stack.T_Label = code;
            _parent.Program.Counter.Increment();
            return true;
        }
    }
}
