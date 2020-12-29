using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Cx : RPN_Function
    {
        public RPN_Function_Cx( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "Cx";
            Description = "Erases X register";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.X.Clear(); 
        }
    }
}
