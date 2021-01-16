using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_arcCOS : RPN_Function
    {
        public RPN_Function_arcCOS( MK52_Host parent):
            base(parent)
        {
            Keyword = "arcCOS";
            Description = "Computes arccosine";
        }

        public override void execute(string code)
        {
            double result = _parent.CalcStack.X.asReal;
            if (_parent.CalcStack.setInvTrigError(result)) return;
            result = Math.Acos(result);
            if( double.IsNaN(result)){
                _parent.CalcStack.setArgumentError();
                return;
            }
            _parent.CalcStack.StorePreviousValue();
            setAngleByMode( result);
        }
    }
}
