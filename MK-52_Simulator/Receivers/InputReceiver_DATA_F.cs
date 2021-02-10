using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator;

namespace MK52Simulator.Receivers
{
    //
    // Implements a receiver for F-modified list
    //
    public class InputReceiver_DATA_F: RPN_InputReceiver
    {
        public InputReceiver_DATA_F(MK52_Host parent)
            : base( parent)
        {
            Moniker = "LIST_F";
            _displayName = " F ";
        }

        public override string tick(RPN_Button button)
        {
            switch (button.Moniker)
            {
                case "Func K":
                    _parent.setReceiver("LIST_K");
                    return "Nothing";
                case "Func A":
                    _parent.setReceiver("LIST_A");
                    return "Nothing";
                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    return "Nothing";
                case "EE":
                    _parent.setReceiver("PORG_N");
                    return "Nothing";
                case "Cx":
                    _parent.setReceiver("LIST_N");
                    return "Nothing";
                default:
                    return "Nothing";
            }                
        }
    }
}
