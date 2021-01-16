using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Minus : RPN_Function
    {
        public RPN_Function_Minus( MK52_Host parent):
            base(parent)
        {
            Keyword = "-";
            Description = "Subtract X from Y";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.Minus();
        }
    }
}
