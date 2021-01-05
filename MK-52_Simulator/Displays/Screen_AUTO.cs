using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator;

namespace MK52Simulator.Displays
{
    //
    // Implements the calculator display in auto mode
    //
    public class Screen_AUTO: RPN_Screen
    {
        public string[] dModeLabels = { "[DEG] ", "[RAD] ", "[GRD] " };

        public Screen_AUTO(RPN_Calculator parent):
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
            StringBuilder sb = new StringBuilder("[");
            sb.Append(_parent.Program.Counter.ToString());
            sb.Append( "] [");
            sb.Append(_parent.Memory.Counter.ToString());
            sb.Append( "] ");
            sb.Append(dModeLabels[_parent.dMode]);
            sb.Append("[");
            sb.Append(_parent.CurrentReceiver.DisplayName);
            sb.Append("] ");
            screenValues[0] = sb.ToString();
            base.makeStatus(screenValues);
        }
        private void makeBody(string[] screenValues)
        {
            _parent.CalcStack.ToStrings( screenValues);
            screenValues[1] = " " + screenValues[1];
            screenValues[2] = screenValues[2].PadLeft(RPN_Display.ScreenWidth);
            screenValues[3] = " " + screenValues[3];
            screenValues[4] = screenValues[4].PadLeft(RPN_Display.ScreenWidth);
            screenValues[5] = " " + screenValues[5];
            screenValues[6] = screenValues[6].PadLeft(RPN_Display.ScreenWidth);
            screenValues[7] = " " + screenValues[7];
            if( !screenValues[8].StartsWith( ">"))
                screenValues[8] = screenValues[8].PadLeft(RPN_Display.ScreenWidth);
        }
        #endregion
    }
}
