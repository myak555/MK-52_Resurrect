using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_ABS : RPN_Function
    {
        public RPN_Function_ABS( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "|X|";
            Description = "Computes modulus X";
        }

        public override void execute()
        {
            RPN_Value result = _parent.XEntry.LoadEditValue();
            _parent.Memory.StorePreviousValue();
            if( result.isInt)
                _parent.Memory.StackValues[0].asInt = -result.asInt;
            else
                _parent.Memory.StackValues[0].asReal = -result.asReal;
        }
    }
}
