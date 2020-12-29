using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_ToDMS : RPN_Function
    {
        public RPN_Function_ToDMS( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "DMS->";
            Description = "Converts DD.dddd into DD.MMSS";
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
            tmp *= 60.0;
            double minutes = Math.Floor(tmp);
            tmp -= minutes;
            double seconds = tmp * 60.0;
            tmp = degrees + (minutes + seconds / 100.0) / 100.0;
            if (negative) tmp = -tmp;         
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.X.asReal = tmp;
        }
    }
}
