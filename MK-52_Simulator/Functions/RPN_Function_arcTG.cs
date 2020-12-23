using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_arcTG : RPN_Function
    {
        public RPN_Function_arcTG( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "arcTG";
            Description = "Computes arctangent";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.Stack.X;
            double result = operand1.asReal;
            result = Math.Atan(result);
            if( double.IsNaN(result)){
                _parent.Stack.setArgumentError();
                return;
            }
            _parent.Stack.StorePreviousValue();
            setAngleByMode( result);
        }
    }
}
