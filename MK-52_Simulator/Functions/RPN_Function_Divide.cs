using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Divide : RPN_Function
    {
        public RPN_Function_Divide( MK52_Host parent):
            base(parent)
        {
            Keyword = "/";
            Description = "Divide Y by X";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.Divide();
        }
    }
}
