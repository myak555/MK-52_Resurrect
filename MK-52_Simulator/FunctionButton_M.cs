using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class FunctionButton_M : Button
    {
        public FunctionButton_M( int X, int Y)
            : base( X, Y)
        {
            standardNCommand = "Mode change";
        }

        public override bool processPress(RPN_Calculator _parent)
        {
            if (_parent.fMode == RPN_Calculator.fMode_Off) return true;
            _parent.dMode++;
            if (_parent.dMode > RPN_Calculator.dMode_Gradian) _parent.dMode = RPN_Calculator.dMode_Degrees;
            return true;
        }
    }
}
