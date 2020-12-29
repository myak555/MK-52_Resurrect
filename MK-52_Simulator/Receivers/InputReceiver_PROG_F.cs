using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a receiver for F-modified buttons
    //
    public class InputReceiver_PROG_F: RPN_InputReceiver
    {
        public InputReceiver_PROG_F(RPN_Calculator parent, RPN_Screen display)
            :
            base( parent, display)
        {
            Moniker = "PROG_F";
            DisplayName = " F ";
        }

        public override void onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                case "Func K":
                    _parent.setReceiver("PROG_K");
                    return;
                case "Func A":
                    _parent.setReceiver("PROG_A");
                    return;

                // Column 5
                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    return;

                case "Cx":
                    _parent.setReceiver("PROG_N");
                    return;
                default:
                    return;
            }                
        }
    }
}
