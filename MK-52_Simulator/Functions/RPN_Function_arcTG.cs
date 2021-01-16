using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_arcTG : RPN_Function
    {
        public RPN_Function_arcTG( MK52_Host parent):
            base(parent)
        {
            Keyword = "arcTG";
            Description = "Computes arctangent";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            double result = operand1.asReal;
            result = Math.Atan(result);
            if( double.IsNaN(result)){
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.StorePreviousValue();
            setAngleByMode( result);
        }
    }
}
