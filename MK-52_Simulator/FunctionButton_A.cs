using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class FunctionButton_A: Button
    {
        public FunctionButton_A(int X, int Y)
            : base(X, Y)
        {
            standardNCommand = "Func A";
        }

        public override bool processPress(RPN_Calculator _parent)
        {
            if (_parent.fMode == RPN_Calculator.fMode_Off) return true;
            _parent.fMode = RPN_Calculator.fMode_A;
            return true;
        }
    }
}
