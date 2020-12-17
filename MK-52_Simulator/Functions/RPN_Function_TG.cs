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
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            if (processAsInt(operand1)) return;
            double result = getRadiansByMode(operand1);
            _parent.setTrigWarning(result);
            result = Math.Tan(result);
            if (double.IsNaN(result))
            {
                _parent.setArgumentError();
                return;
            }
            _parent.Memory.StorePreviousValue();
            setAngleByMode( result);
        }

        private bool processAsInt(RPN_Value o)
        {
            int[] octValues = { 0, 1, 0, -1 };
            int oct = getTrigOctant(o);
            if (oct < 0) return false;
            if (oct == 2)
            {
                _parent.setInfinityError();
                return true;
            }
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asInt = octValues[oct];
            return true;
        }
    }
}
