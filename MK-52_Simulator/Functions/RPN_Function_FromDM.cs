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

        public override void execute()
        {
            RPN_Value operand1 = _parent.XEntry.LoadEditValue();
            double tmp = operand1.asReal;
            bool negative = false;
            if (tmp < 0)
            {
                negative = true;
                tmp = -tmp;
            }
            double degrees = Math.Floor(tmp);
            tmp -= degrees;
            tmp *= 100.0;
            double minutes = Math.Floor(tmp);
            if (minutes >= 60.0)
            {
                _parent.setDegError();
                return;
            }
            tmp = degrees + minutes / 60.0;
            if (negative) tmp = -tmp;         
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asReal = tmp;
        }
    }
}
