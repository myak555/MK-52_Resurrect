using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_AXtoM : RPN_Function
    {
        public RPN_Function_AXtoM( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "AX->M ";
            Description = "Put value from register X into extended memory";
            containsRegister = true;
        }

        public override void execute(string code)
        {
            code = code.Substring(Keyword.Length).Trim();
            _parent.Memory.FromStack( Convert.ToInt32(code));
        }
    }
}
