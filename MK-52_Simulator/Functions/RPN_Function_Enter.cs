using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Enter : RPN_Function
    {
        public RPN_Function_Enter( RPN_Calculator parent): base(parent)
        {
            Keyword = "Enter";
            Description = "Enters value into the stack";
        }

        public override void execute()
        {
            _parent.Memory.StorePreviousValue();
            _parent.XEntry.LoadEditValue();

            // This button has special condition on exit - stack is pushed once
            _parent.Memory.PushStack(1);
            _parent.XEntry.pushOnEntryRequired = false;
        }
    }
}
