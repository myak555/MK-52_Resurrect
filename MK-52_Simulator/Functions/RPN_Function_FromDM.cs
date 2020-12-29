using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_FromDM : RPN_Function
    {
        public RPN_Function_FromDM(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "<-DM";
            Description = "Converts DD.MMmmm into DD.dddd";
        }

        public override void execute(string code)
        {
            double result = _parent.CalcStack.X.asReal;
            bool negative = false;
            if (result < 0)
            {
                negative = true;
                result = -result;
            }
            double degrees = Math.Floor(result);
            result -= degrees;
            double minutes = result * 100.0;
            if (minutes >= 60.0)
            {
                _parent.CalcStack.setDegError();
                return;
            }
            result = degrees + minutes / 60.0;
            if (negative) result = -result;
            _parent.CalcStack.Replace(result);
        }
    }
}
