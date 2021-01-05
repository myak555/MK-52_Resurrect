using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_LblX : RPN_Function
    {
        public RPN_Function_LblX( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "LX>";
            Description = "Puts value into X Label";
        }

        public override void execute(string code)
        {
            string tmp = code.Substring(Keyword.Length).Trim();
            _parent.CalcStack.X_Label = (tmp.Length == 0) ? "X:" : tmp;
        }
    }
}
