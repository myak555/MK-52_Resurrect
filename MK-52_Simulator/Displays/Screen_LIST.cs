using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator.Displays
{
    //
    // Implements the calculator display in memory listing mode
    //
    public class Screen_LIST: RPN_Screen
    {
        public Screen_LIST( RPN_Calculator parent):
            base(parent)
        {
        }

        public override void setScreenValues(string[] screenValues)
        {
            makeStatus(screenValues);
            makeBody(screenValues);
        }

        #region Private Functions
        private string presentValue(RPN_Value v)
        {
            return v.ToString().PadLeft(RPN_Display.ScreenWidth);
        }
        protected override void makeStatus(string[] screenValues)
        {
            StringBuilder sb = new StringBuilder("[");
            sb.Append( _parent.Program.Counter.ToString());
            sb.Append("] [");
            sb.Append(_parent.CurrentReceiver.DisplayName);
            sb.Append("]");
            screenValues[0] = sb.ToString();
            base.makeStatus(screenValues);
        }
        private void makeBody(string[] screenValues)
        {
            for (int i = -7, j=1; j <= 8; i++, j++)
            {
                int dl = _parent.Memory.Counter.V + i;
                screenValues[j] = "";
                if (dl < 0) continue;
                if (dl >= RPN_Memory.ExtendedMemorySize) continue;
                StringBuilder sb = new StringBuilder();
                sb.Append(dl.ToString("000"));
                sb.Append((i == 0) ? "> " : "  ");
                //sb.Append((j == 8 && _parent.X_Entry.Mode != RPN_Number_Entry.Mode_Off) ?
                //    _parent.X_Entry.ToString() :
                sb.Append(_parent.Memory.GetLine(dl).ToString().PadLeft(RPN_Display.ScreenWidth - 5));
                screenValues[j] = sb.ToString();
            }
        }
        #endregion
    }
}
