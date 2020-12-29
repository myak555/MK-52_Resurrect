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
    public class InputReceiver_PROG_N: RPN_InputReceiver
    {
        public InputReceiver_PROG_N(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "PROG_N";
        }

        public override void onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("PROG_F");
                    return;
                case "Func K":
                    _parent.setReceiver("PROG_K");
                    return;
                case "Func A":
                    _parent.setReceiver("PROG_A");
                    return;

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    return;
                case "<-":
                    _parent.Program.Counter.Decrement();
                    return;
                case "B/O":
                    return;
                case "S/P":
                    return;

                default:
                    return;
            }                
        }
    }
}
