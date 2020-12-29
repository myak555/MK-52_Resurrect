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

        public override void execute(string code)
        {
            _parent.CalcStack.T_Label = code.Substring(Keyword.Length).Trim();
        }
    }
}
