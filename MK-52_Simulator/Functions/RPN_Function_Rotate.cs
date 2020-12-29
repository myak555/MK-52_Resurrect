using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Rotate : RPN_Function
    {
        public RPN_Function_Rotate( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "Rotate";
            Description = "Rotates stack (X to T)";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = new RPN_Value( _parent.CalcStack.X);
            _parent.CalcStack.Rotate();
        }
    }
}
