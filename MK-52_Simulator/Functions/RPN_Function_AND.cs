using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_AND : RPN_Function
    {
        public RPN_Function_AND( MK52_Host parent):
            base(parent)
        {
            Keyword = "AND";
            Description = "Computes logical AND between X and Y (as integers)";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            RPN_Value operand2 = _parent.CalcStack.Y;
            Int64 result = operand1.asInt & operand2.asInt;
            _parent.CalcStack.Pop(2);
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asInt = result;
        }
    }
}
