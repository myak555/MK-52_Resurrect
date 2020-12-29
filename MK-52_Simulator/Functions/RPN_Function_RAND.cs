using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_RAND : RPN_Function
    {
        public RPN_Function_RAND( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "RAND";
            Description = "Computes pseudo-random value";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.Push(1);
            _parent.CalcStack.X.asReal = _parent.myRNG.NextDouble();
        }
    }
}
