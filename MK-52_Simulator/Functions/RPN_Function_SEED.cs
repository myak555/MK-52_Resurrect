using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_SEED : RPN_Function
    {
        public RPN_Function_SEED( MK52_Host parent):
            base(parent)
        {
            Keyword = "SEED";
            Description = "Sets seed for the pseudo-random generator";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            _parent.myRNG = new Random( (int)(operand1.asInt | 0xFFFFFFFF));
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.Pop(1);
        }
    }
}
