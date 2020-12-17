using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_arcSIN : RPN_Function
    {
        public RPN_Function_arcSIN( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "arcSIN";
            Description = "Computes arcsine";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            double result = operand1.asReal;
            if( _parent.setInvTrigError( result)) return;
            result = Math.Asin(result);
            if( double.IsNaN(result)){
                _parent.setArgumentError();
                return;
            }
            _parent.Memory.StorePreviousValue();
            setAngleByMode( result);
        }
    }
}
