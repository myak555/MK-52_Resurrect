using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_SIN : RPN_Function
    {
        public RPN_Function_SIN( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "SIN";
            Description = "Computes sine";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.Stack.X;
            if(  processAsInt(operand1)) return;
            double result = getRadiansByMode( operand1);
            _parent.Stack.setTrigWarning(result);
            result = Math.Sin(result);
            if (double.IsNaN(result))
            {
                _parent.Stack.setArgumentError();
                return;
            }
            _parent.Stack.Replace( result);
        }

        private bool processAsInt( RPN_Value o)
        {
            int[] quadValues = { 0, 1, 0, -1};  
            int quad = getTrigQuadrant( o);
            if( quad<0) return false;
            _parent.Stack.StorePreviousValue();
            _parent.Stack.X.asInt = quadValues[quad];
            return true;
        }
    }
}
