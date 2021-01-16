using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_RAND : RPN_Function
    {
        public RPN_Function_RAND( MK52_Host parent):
            base(parent)
        {
            Keyword = "RAND";
            Description = "Computes pseudo-random value";
        }

        public override void execute(string code)
        {
            _parent.CalcStack.Push(_parent.myRNG.NextDouble());
        }
    }
}
