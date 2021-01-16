using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_TG : RPN_Function
    {
        public RPN_Function_TG( MK52_Host parent):
            base(parent)
        {
            Keyword = "TG";
            Description = "Computes tangent";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            if (processAsInt(operand1)) return;
            double result = getRadiansByMode(operand1);
            _parent.CalcStack.setTrigWarning(result);
            result = Math.Tan(result);
            if (double.IsNaN(result))
            {
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.Replace( result);
        }

        private bool processAsInt(RPN_Value o)
        {
            int[] octValues = { 0, 1, 0, -1 };
            int oct = getTrigOctant(o);
            if (oct < 0) return false;
            if (oct == 2)
            {
                _parent.CalcStack.setInfinityError();
                return true;
            }
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asInt = octValues[oct];
            return true;
        }
    }
}
