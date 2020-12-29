using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Enter : RPN_Function
    {
        public RPN_Function_Enter( RPN_Calculator parent): base(parent)
        {
            Keyword = "Enter";
            Description = "Enters value into the stack";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.Push();
        }
    }
}
