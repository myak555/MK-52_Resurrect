using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the calculator display in file mode
    //
    public class Display_FILE : Display
    {
        public Display_FILE()
        {
            Moniker = "FILE";
        }

        public override void activate(string prevDisplay)
        {
            if (prevDisplay == Moniker)
            {
                updateBody();
                return;
            }
            LCD_Manager lm = _parent._m_Hardware_LCD;
            lm.clearScreen();
            base.activate(prevDisplay);
            string[] Lines = _parent._m_RPN_Functions.getOutputLines();
            _parent._m_Hardware_SD.getFolderListing(Lines, 11, LCD_Manager.SCREEN_COLS - 1);
            for (int i = 0; i < 11; i++)
            {
                lm.outputTerminalLine((uint)i, Lines[i]);
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
