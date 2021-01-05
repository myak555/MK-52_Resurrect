using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_AMtoX : RPN_Function
    {
        public RPN_Function_AMtoX( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "AM->X ";
            Description = "Puts value from extended memory into register X";
            containsAddress = true;
        }

        public override void execute(string code)
        {
            code = code.Substring(Keyword.Length).Trim();
            _parent.Memory.ToStack( Convert.ToInt32(code));
        }
    }
}
