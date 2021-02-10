using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the calculator display in memory listing mode
    //
    public class Display_DATA : Display
    {
        public Display_DATA( MK52_Host parent):
            base(parent)
        {
            Moniker = "DATA";
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
            for (int i=-10, j=1; j<=10; i++, j++)
            {
                int dl = _parent.Memory.Counter.V + i;
                target.eraseTerminalLine((uint)j);
                if (dl < 0) continue;
                if (dl >= RPN_Memory.ExtendedMemorySize) continue;
                StringBuilder sb = new StringBuilder();
                sb.Append(dl.ToString("0000"));
                sb.Append((i == 0) ? "> " : "  ");
                sb.Append(_parent.Memory.GetLine(dl).ToString().PadLeft(LCD_Manager.SCREEN_COLS - 6));
                target.outputTerminalLine( (uint)j, sb.ToString());
            }
        }
        #endregion
    }
}
