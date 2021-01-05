using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LblY : RPN_Function
    {
        public RPN_Function_LblY( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "LY>";
            Description = "Puts value into Y Label";
        }

        public override void execute(string code)
        {
            string tmp = code.Substring(Keyword.Length).Trim();
            _parent.CalcStack.Y_Label = (tmp.Length == 0) ? "Y:" : tmp;
        }
    }
}
