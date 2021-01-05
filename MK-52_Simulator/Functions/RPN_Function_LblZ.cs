using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LblZ : RPN_Function
    {
        public RPN_Function_LblZ( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "LZ>";
            Description = "Puts value into Z Label";
        }

        public override void execute(string code)
        {
            string tmp = code.Substring(Keyword.Length).Trim();
            _parent.CalcStack.Z_Label = (tmp.Length == 0) ? "Z:" : tmp;
        }
    }
}
