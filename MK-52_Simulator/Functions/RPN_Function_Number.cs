using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_Number : RPN_Function
    {
        private const string allowedChars = ".0123456789eE+-";

        //
        // Tries to process a generic number into stack X value
        //
        public RPN_Function_Number(RPN_Calculator parent)
            : base(parent)
        {
            Keyword = "Number";
            Description = "Sends a number into stack X";
        }

        public override bool executeProgram(string code)
        {
            code = code.Trim();
            for (int i = 0; i < code.Length; i++)
            {
                if( allowedChars.IndexOf( code[i]) >= 0) continue;
                return false;
            }
            try
            {
                double tmp = Convert.ToDouble(code);
                _parent.Stack.StorePreviousValue();
                _parent.Stack.Push(1);
                _parent.Stack.X.asReal = tmp;
                _parent.Program.Counter.Increment();
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
