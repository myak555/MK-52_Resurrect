using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Displays
{
    //
    // Implements the calculator display in OFF mode
    //
    public class Display_OFF : Display
    {
        public Display_OFF(MK52_Host parent):
            base( parent)
        {
            Moniker = "OFF";
        }

        public override string activate()
        {
            _parent.LCD.clearScreen();
            return Moniker;
        }
    }
}
