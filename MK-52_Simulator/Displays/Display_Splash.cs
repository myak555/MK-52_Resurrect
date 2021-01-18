using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Displays
{
    //
    // Implements the calculator display in OFF mode
    //
    public class Display_Splash : Display
    {
        public Display_Splash(MK52_Host parent)
            : base( parent)
        {
            Moniker = "Splash";
        }

        public override string activate()
        {
            _parent.LCD.clearScreen();
            _parent.LCD.showSplash();
            return Moniker;
        }
    }
}