using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_RETURN : RPN_Function
    {
        public RPN_Function_RETURN(MK52_Host parent)
            : base(parent)
        {
            Keyword = "RETURN";
            Description = "Returns from a subroutine";
        }

        public override void execute(string code)
        {
            if( _parent.CallStack.Count == 0)
                _parent.Program.Counter.Set(0);
            _parent.Program.Counter.Set( _parent.CallStack.Pop()); 
        }
    }
}
