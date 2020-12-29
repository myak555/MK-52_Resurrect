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

        public override bool executeCODE(string code)
        {
            if (code == "-") return false;
            for (int i = 0; i < code.Length; i++)
            {
                if( allowedChars.IndexOf( code[i]) >= 0) continue;
                return false;
            }
            try
            {
                double result = Convert.ToDouble(code);
                _parent.CalcStack.Push(result);
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
