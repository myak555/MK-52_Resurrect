using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_MAX : RPN_Function
    {
        public RPN_Function_MAX( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "MAX";
            Description = "Leaves maximum between X and Y";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            RPN_Value operand2 = _parent.CalcStack.Y;
            bool result = operand1.asReal > operand2.asReal;
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.Pop(result? 2: 1);
        }
    }
}
