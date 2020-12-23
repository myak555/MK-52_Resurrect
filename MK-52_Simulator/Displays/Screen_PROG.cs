using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator.Displays
{
    //
    // Implements the calculator display in auto mode
    //
    public class Screen_PROG:RPN_Screen
    {
        public string[] aModeLabels = { "[CODE] ", "[TEXT] ", "[NUMB]" };

        public Screen_PROG(RPN_Calculator parent):
            base( parent)
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
            StringBuilder sb = new StringBuilder();
            sb.Append(aModeLabels[_parent.aMode]);
            sb.Append("[");
            sb.Append(_parent.Memory.Counter.ToString());
            sb.Append("] ");
            screenValues[0] = sb.ToString();
            base.makeStatus(screenValues);
        }
        private void makeBody(string[] screenValues)
        {
            for (int i = -7, j=1; j <= 8; i++, j++)
            {
                int dl = _parent.Program.Counter.V + i;
                screenValues[j] = "";
                if (dl < 0) continue;
                if (dl >= RPN_Program.ProgramSize) continue;
                StringBuilder sb = new StringBuilder();
                sb.Append(dl.ToString("000"));
                sb.Append((i == 0) ? "> " : "  ");
                sb.Append(_parent.Program.GetLine( dl));
                screenValues[j] = sb.ToString();
            }
        }
        #endregion
    }
}
