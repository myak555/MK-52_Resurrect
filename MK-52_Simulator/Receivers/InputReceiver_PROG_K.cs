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
            _displayName = " K ";
        }

        public override void onButton(RPN_Button button)
        {
            if (_parent.Program.Counter.isActive)
            {

                if (_parent.Program.Counter.onButton(button, false))
                {
                    _parent.Program.AppendCounterString();
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("PROG_N");
                }
                return;
            }
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("PROG_F");
                    return;
                case "Func A":
                    _parent.setReceiver("PROG_A");
                    return;
                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    _parent.Shutdown();
                    return;

                // Column 1
                case "->":
                    _parent.Program.SetCurrentLine("IFNOT X<Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return;
                case "<-":
                    _parent.Program.SetCurrentLine("IFNOT X==Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return;
                case "B/O":
                    _parent.Program.SetCurrentLine("IFNOT X>=Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return;
                case "S/P":
                    _parent.Program.SetCurrentLine("IFNOT X!=Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return;

                // Column 2
                case "M->X":
                    _parent.Program.SetCurrentLine("LT> ");
                    //_parent.Program.Counter.ActivateEntry();
                    _parent.Program.Counter.Increment();
                    return;
                case "X->M":
                    _parent.Program.SetCurrentLine("LZ> ");
                    //_parent.Program.Counter.ActivateEntry();
                    _parent.Program.Counter.Increment();
                    return;
                case "GOTO":
                    _parent.Program.SetCurrentLine("LY> ");
                    //_parent.Program.Counter.ActivateEntry();
                    _parent.Program.Counter.Increment();
                    return;
                case "GOSUB":
                    _parent.Program.SetCurrentLine("LX> ");
                    //_parent.Program.Counter.ActivateEntry();
                    _parent.Program.Counter.Increment();
                    return;

                default:
                    return;
            }                
        }
    }
}
