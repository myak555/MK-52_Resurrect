using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_KXtoM : RPN_Function
    {
        public RPN_Function_KXtoM( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "KX->M";
            Description = "Puts value into memory by an address in register";
        }

        public override void execute(string code)
        {
            code = code.Substring(Keyword.Length).Trim();
            _parent.Registers.FromStackToMemory(code);
        }
    }
}
