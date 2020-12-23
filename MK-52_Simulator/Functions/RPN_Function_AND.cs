using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Functions
{
    public class RPN_Function_AND : RPN_Function
    {
        public RPN_Function_AND( RPN_Calculator parent):
            base(parent)
        {
            Keyword = "AND";
            Description = "Computes logical AND between X and Y (as integers)";
        }

        public override void execute()
        {
            RPN_Value operand1 = _parent.Stack.X;
            RPN_Value operand2 = _parent.Stack.Y;
            Int64 result = operand1.asInt & operand2.asInt;
            _parent.Stack.Pop(2);
            _parent.Stack.StorePreviousValue();
            _parent.Stack.X.asInt = result;
        }
    }
}
