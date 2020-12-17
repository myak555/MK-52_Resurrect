using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_COS : RPN_Function
    {
        public RPN_Function_COS( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "COS";
            Description = "Computes cosine";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            if (processAsInt(operand1)) return;
            double result = getRadiansByMode(operand1);
            _parent.setTrigWarning(result);
            result = Math.Cos(result);
            if (double.IsNaN(result))
            {
                _parent.setArgumentError();
                return;
            }
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asReal = result;
        }

        private bool processAsInt(RPN_Value o)
        {
            int[] quadValues = { 1, 0, -1, 0 };
            int quad = getTrigQuadrant( o);
            if (quad < 0) return false;
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asInt = quadValues[quad];
            return true;
        }
    }
}
