using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Mult : RPN_Function
    {
        public RPN_Function_Mult( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "*";
            Description = "Multiply X and Y";
        }

        public override void execute()
        {
            RPN_Value result = RPN_Value.Multiply( _parent.Memory.StackValues[1], _parent.XEntry.LoadEditValue()); 
            _parent.Memory.PopStack(2);
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].FromRPNValue( result);
        }
    }
}
