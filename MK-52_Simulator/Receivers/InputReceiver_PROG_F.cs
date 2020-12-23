using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic empty receiver
    //
    public class InputReceiver_PROG_F: RPN_InputReceiver
    {
        public InputReceiver_PROG_F(RPN_Calculator parent, RPN_Screen display)
            :
            base( parent, display)
        {
            Moniker = "PROG_F";
            DisplayName = "  F  ";
        }

        public override bool onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                case "Func K":
                    _parent.setReceiver("PROG_K");
                    return true;
                case "Func A":
                    _parent.setReceiver("PROG_A");
                    return true;

                // Column 5
                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    return true;

                case "Cx":
                    _parent.setReceiver("PROG_N");
                    return true;
                default:
                    return false;
            }                
        }
    }
}
