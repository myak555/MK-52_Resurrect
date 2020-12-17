using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_FromDMS : RPN_Function
    {
        public RPN_Function_FromDMS(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "<-DMS";
            Description = "Converts DD.MMSSss into DD.dddd";
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
            tmp -= minutes;
            double seconds = tmp * 100.0;
            if (seconds >= 60.0)
            {
                _parent.setDegError();
                return;
            }
            tmp = degrees + (minutes + seconds / 60.0) / 60.0;
            if (negative) tmp = -tmp;         
            _parent.Memory.StorePreviousValue();
            _parent.Memory.StackValues[0].asReal = tmp;
        }
    }
}
