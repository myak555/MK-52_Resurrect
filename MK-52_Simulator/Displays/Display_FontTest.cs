using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the calculator display in Splash mode
    //
    public class Display_FontTest : Display
    {
        public Display_FontTest()
        {
            Moniker = "Font Test";
        }

        public override void activate(string prevDisplay)
        {
            LCD_Manager lm = _parent._m_Hardware_LCD;
            lm.clearScreen();
            for (int i = 0; i < 256; i++)
            {
                int x = (i % 29) * 11;
                int y = (i / 29) * 20;
                lm.outputChar(x, y, (byte)i, System.Drawing.Color.Orange, System.Drawing.Color.Black);
            }
            lm.Refresh();
        }
    }
}
