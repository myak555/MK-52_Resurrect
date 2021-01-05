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
    public class InputReceiver_LIST_A: RPN_InputReceiver
    {
        public InputReceiver_LIST_A(RPN_Calculator parent, RPN_Screen display)
            :
            base( parent, display)
        {
            Moniker = "LIST_A";
            _displayName = " A ";
        }

        public override void onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("LIST_F");
                    return;
                case "Func K":
                    _parent.setReceiver("LIST_K");
                    return;

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    return;
                case "<-":
                    _parent.Program.Counter.Decrement();
                    return;
                case "B/O":
                    _parent.Program.Counter.Set(0);
                    return;

                case "EE":
                    _parent.setReceiver("LIST_N");
                    return;

                case "Cx":
                    _parent.setReceiver("LIST_N");
                    _parent.Shutdown();
                    return;
                default:
                    return;
            }                
        }
    }
}
