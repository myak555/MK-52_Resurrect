using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic empty receiver
    //
    public class InputReceiver_DATA_K: RPN_InputReceiver
    {
        public InputReceiver_DATA_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "LIST_K";
            _displayName = " K ";
        }

        public override string tick(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("LIST_F");
                    return "Nothing";
                case "Func A":
                    _parent.setReceiver("LIST_A");
                    return "Nothing";

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("LIST_N");
                    return "Nothing";
                case "<-":
                    _parent.Program.Counter.Decrement();
                    _parent.setReceiver("LIST_N");
                    return "Nothing";
                case "B/O":
                    _parent.Program.Counter.Set(0);
                    _parent.setReceiver("LIST_N");
                    return "Nothing";

                default:
                    return "Nothing";
            }                
        }
    }
}
