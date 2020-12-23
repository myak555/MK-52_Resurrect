using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_TG : RPN_Function
    {
        public RPN_Function_TG( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "TG";
            Description = "Computes tangent";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.Stack.X;
            if (processAsInt(operand1)) return;
            double result = getRadiansByMode(operand1);
            _parent.Stack.setTrigWarning(result);
            result = Math.Tan(result);
            if (double.IsNaN(result))
            {
                _parent.Stack.setArgumentError();
                return;
            }
            _parent.Stack.Replace( result);
        }

        private bool processAsInt(RPN_Value o)
        {
            int[] octValues = { 0, 1, 0, -1 };
            int oct = getTrigOctant(o);
            if (oct < 0) return false;
            if (oct == 2)
            {
                _parent.Stack.setInfinityError();
                return true;
            }
            _parent.Stack.StorePreviousValue();
            _parent.Stack.X.asInt = octValues[oct];
            return true;
        }
    }
}
