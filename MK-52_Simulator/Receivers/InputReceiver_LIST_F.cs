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
    public class InputReceiver_LIST_F: RPN_InputReceiver
    {
        public InputReceiver_LIST_F(RPN_Calculator parent, RPN_Screen display)
            :
            base( parent, display)
        {
            Moniker = "LIST_F";
            DisplayName = "  F  ";
        }

        public override bool onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                case "Func K":
                    _parent.setReceiver("LIST_K");
                    return true;
                case "Func A":
                    _parent.setReceiver("LIST_A");
                    return true;
                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "EE":
                    _parent.setReceiver("PORG_N");
                    return true;
                case "Cx":
                    _parent.setReceiver("LIST_N");
                    return true;
                default:
                    return false;
            }                
        }
    }
}
