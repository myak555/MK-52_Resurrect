using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the calculator display for running programs
    //
    public class Display_RUN : Display
    {
        public Display_RUN(MK52_Host parent):
            base( parent)
        {
            Moniker = "RUN";
        }

        public override string activate()
        {
            base.activate();
            return Moniker;
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
                int dl = _parent.Program.Counter.V + i;
                target.eraseTerminalLine((uint)j);
                if (dl < 0) continue;
                if (dl >= RPN_Program.ProgramSize) continue;
                StringBuilder sb = new StringBuilder();
                sb.Append(dl.ToString("0000"));
                sb.Append((i == 0) ? "> " : "  ");
                target.outputTerminalLine((uint)j, sb.ToString());
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
