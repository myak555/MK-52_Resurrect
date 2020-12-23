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
    public class InputReceiver_LIST_N: RPN_InputReceiver
    {
        public InputReceiver_LIST_N(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "LIST_N";
        }

        public override bool onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("LIST_F");
                    return true;
                case "Func K":
                    _parent.setReceiver("LIST_K");
                    return true;
                case "Func A":
                    _parent.setReceiver("LIST_A");
                    return true;

                // Column 1
                case "->":
                    _parent.Memory.Counter.Increment();
                    _parent.setReceiver("LIST_N");
                    return true;
                case "<-":
                    _parent.Memory.Counter.Decrement();
                    _parent.setReceiver("LIST_N");
                    return true;
                case "B/O":
                    _parent.Memory.Counter.Set(0);
                    _parent.setReceiver("LIST_N");
                    return true;

                default:
                    return false;
            }                
        }
    }
}
