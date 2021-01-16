using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_KMtoX : RPN_Function
    {
        public RPN_Function_KMtoX( MK52_Host parent):
            base(parent)
        {
            Keyword = "KM->X";
            Description = "Indirect value from memory via a register";
            containsRegister = true;
        }

        public override void execute(string code)
        {
            code = code.Substring(Keyword.Length).Trim();
            _parent.Registers.FromMemoryToStack( code);
        }
    }
}
