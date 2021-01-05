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
    public class InputReceiver_LIST_K: RPN_InputReceiver
    {
        public InputReceiver_LIST_K(RPN_Calculator parent, RPN_Screen display)
            :
            base( parent, display)
        {
            Moniker = "LIST_K";
            _displayName = " K ";
        }

        public override void onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("LIST_F");
                    return;
                case "Func A":
                    _parent.setReceiver("LIST_A");
                    return;

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("LIST_N");
                    return;
                case "<-":
                    _parent.Program.Counter.Decrement();
                    _parent.setReceiver("LIST_N");
                    return;
                case "B/O":
                    _parent.Program.Counter.Set(0);
                    _parent.setReceiver("LIST_N");
                    return;

                default:
                    return;
            }                
        }
    }
}
