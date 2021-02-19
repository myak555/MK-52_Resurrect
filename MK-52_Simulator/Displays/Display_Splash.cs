using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the calculator display in Splash mode
    //
    public class Display_Splash : Display
    {
        public Display_Splash()
        {
            Moniker = "Splash";
        }

        public override void activate(string prevDisplay)
        {
            LCD_Manager lm = _parent._m_Hardware_LCD;
            lm.clearScreen();
            lm.showSplash();
            lm.Refresh();
        }
    }
}
