using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Rotate : RPN_Function
    {
        public RPN_Function_Rotate( MK52_Host parent):
            base(parent)
        {
            Keyword = "Rotate";
            Description = "Rotates stack (X to T)";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.Rotate();
        }
    }
}
