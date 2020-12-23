using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Displays
{
    //
    // Implements the calculator display in OFF mode
    //
    public class Screen_OFF: RPN_Screen
    {
        public Screen_OFF(RPN_Calculator parent):
            base( parent)
        {
        }

        public override void setScreenValues(string[] screenValues)
        {
            for (int i = 0; i < screenValues.Length; i++)
                screenValues[i] = "";
        }
    }
}
