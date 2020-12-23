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
            double result = _parent.Stack.X.asReal;
            if (_parent.Stack.setInvTrigError(result)) return;
            result = Math.Asin(result);
            if( double.IsNaN(result)){
                _parent.Stack.setArgumentError();
                return;
            }
            _parent.Stack.StorePreviousValue();
            setAngleByMode( result);
        }
    }
}
