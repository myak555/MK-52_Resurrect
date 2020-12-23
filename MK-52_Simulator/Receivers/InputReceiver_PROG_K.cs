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
    public class InputReceiver_PROG_K: RPN_InputReceiver
    {
        public InputReceiver_PROG_K(RPN_Calculator parent, RPN_Screen display)
            :
            base( parent, display)
        {
            Moniker = "PROG_K";
            DisplayName = "  K  ";
        }

        public override bool onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("PROG_F");
                    return true;
                case "Func A":
                    _parent.setReceiver("PROG_A");
                    return true;
                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    _parent.Shutdown();
                    return true;

                // Column 1
                case "->":
                    _parent.Memory.Counter.Increment();
                    _parent.setReceiver("PROG_N");
                    return true;
                case "<-":
                    _parent.Memory.Counter.Decrement();
                    _parent.setReceiver("PROG_N");
                    return true;
                case "B/O":
                    _parent.Program.Counter.Set(0);
                    _parent.setReceiver("PROG_N");
                    return true;

                default:
                    return false;
            }                
        }
    }
}
