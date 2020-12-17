using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Divide : RPN_Function
    {
        public RPN_Function_Divide( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "/";
            Description = "Divide Y by X";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            if( operand1.asReal == 0.0)
            {
                _parent.setInfinityError();
                return;
            }
            RPN_Value result = RPN_Value.Divide(_parent.Memory.StackValues[1], operand1); 
            _parent.Memory.PopStack(2);
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].FromRPNValue(result);
        }
    }
}
