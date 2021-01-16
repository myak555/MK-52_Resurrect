using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_ToDM : RPN_Function
    {
        public RPN_Function_ToDM(MK52_Host parent)
            : base(parent)
        {
            Keyword = "DM->";
            Description = "Converts DD.dddd into DD.MMmmm";
        }

        public override void execute(string code)
        {
            RPN_Value operand1 = _parent.CalcStack.X;
            double tmp = operand1.asReal;
            bool negative = false;
            if (tmp < 0)
            {
                negative = true;
                tmp = -tmp;
            }
            double degrees = Math.Floor(tmp);
            tmp -= degrees;
            double minutes = tmp * 60.0;
            tmp = degrees + minutes / 100.0;
            if (negative) tmp = -tmp;         
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asReal = tmp;
        }
    }
}
