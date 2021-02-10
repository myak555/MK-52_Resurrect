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
    public class InputReceiver_DATA_A: RPN_InputReceiver
    {
        public InputReceiver_DATA_A(MK52_Host parent)
            : base( parent)
        {
            Moniker = "LIST_A";
            _displayName = " A ";
        }

        public override string tick(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("LIST_F");
                    return "Nothing";
                case "Func K":
                    _parent.setReceiver("LIST_K");
                    return "Nothing";

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    return "Nothing";
                case "<-":
                    _parent.Program.Counter.Decrement();
                    return "Nothing";
                case "B/O":
                    _parent.Program.Counter.Set(0);
                    return "Nothing";

                case "EE":
                    _parent.setReceiver("LIST_N");
                    return "Nothing";

                case "Cx":
                    _parent.setReceiver("LIST_N");
                    _parent.Shutdown();
                    return "Nothing";
                default:
                    return "Nothing";
            }                
        }
    }
}
