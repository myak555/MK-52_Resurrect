using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the calculator display in programming mode
    //
    public class Display_PROG : Display
    {
        public Display_PROG()
        {
            Moniker = "PROG";
        }

        public override void activate(string prevDisplay)
        {
            if (prevDisplay == Moniker)
            {
                updateBody();
                return;
            }
            LCD_Manager lm = _parent._m_Hardware_LCD;
            Program_Memory pm = _parent._m_Program_Memory;
            lm.clearScreen();
            lm.outputStatus(
                pm.getCounter(),
                _parent._m_Extended_Memory.getCounter(),
                pm.getEModeName(),
                "   ");
            int display_PC = (int)pm.getCounter();
            string[] _displayLines = pm.getPreviousLines( LCD_Manager.SCREEN_ROWS - 1);
            for (int i = 10, j = 0, k = display_PC; i >= 0; i--, j++, k--)
            {
                if (k < 0)
                {
                    lm.eraseTerminalLine((uint)i);
                    continue;
                }
                string s = k.ToString("0000");
                s += (k==display_PC)? "> ": "  ";
                lm.outputTerminalLine((uint)i, s + _displayLines[j]);
            }
            lm.Refresh();
        }

        //public override void tick()
        //{
        //    return;
        //}

        //public override void setScreenValues(LCD_Manager target)
        //{
        //    makeStatus(target);
        //    makeBody(target);
        //}

        #region Private Functions

        private void makeBody(LCD_Manager target)
        {
            for (int i = -10, j = 1; j <= 10; i++, j++)
            {
                //int dl = _parent._m_Program_Memory.Counter.V + i;
                //target.eraseTerminalLine((uint)j);
                //if (dl < 0) continue;
                //if (dl >= Program_Memory.ProgramSize) continue;
                //StringBuilder sb = new StringBuilder();
                //sb.Append(dl.ToString("0000"));
                //sb.Append((i == 0) ? "> " : "  ");
                //target.outputTerminalLine((uint)j, sb.ToString());
                //if (j < 8)
                //{
                //    sb.Append(GetLine(dl));
                //    inp[j] = sb.ToString();
                //    continue;
                //}
                //if (Number.isActive)
                //{
                //    sb.Append(Number.ToString());
                //    inp[j] = sb.ToString();
                //    continue;
                //}
                //if (Text.isActive)
                //{
                //    sb.Append(Text.ToString());
                //    inp[j] = sb.ToString();
                //    continue;
                //}
                //if (Counter.isActive)
                //{
                //    sb.Append(GetLine(dl));
                //    sb.Append(Counter.ActiveEntry);
                //    inp[j] = sb.ToString();
                //    continue;
                //}
                //sb.Append(GetLine(dl));
                //inp[j] = sb.ToString();
            }

            //_parent.Program.ToStrings(screenValues);
        }
        #endregion
    }
}
