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
        public InputReceiver_PROG_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_K";
            _displayName = " K ";
        }

        public override string tick(RPN_Button button)
        {
            if (_parent.Program.Counter.isActive)
            {

                if (_parent.Program.Counter.onButton(button, false))
                {
                    _parent.Program.AppendCounterString();
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("PROG_N");
                }
                return "Nothing";
            }
            if (_parent.Registers.isActive)
            {

                if (_parent.Registers.onButton(button))
                {
                    _parent.Registers.AppendRegisterString();
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("PROG_N");
                }
                return "Nothing";
            }
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("PROG_F");
                    return "Nothing";
                case "Func A":
                    _parent.setReceiver("PROG_A");
                    return "Nothing";
                case "Mode":
                    _parent.Program.SetCurrentLine("RAD");
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("PROG_N");
                    return "Nothing";

                // Column 1
                case "->":
                    _parent.Program.SetCurrentLine("IFNOT X<Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return "Nothing";
                case "<-":
                    _parent.Program.SetCurrentLine("IFNOT X==Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return "Nothing";
                case "B/O":
                    _parent.Program.SetCurrentLine("IFNOT X>=Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return "Nothing";
                case "S/P":
                    _parent.Program.SetCurrentLine("IFNOT X!=Y GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return "Nothing";

                // Column 2
                case "M->X":
                    _parent.Program.SetCurrentLine("KM->X ");
                    _parent.Registers.ActivateEntry(RPN_Registers.None);
                    return "Nothing";
                case "X->M":
                    _parent.Program.SetCurrentLine("KX->M ");
                    _parent.Registers.ActivateEntry(RPN_Registers.None);
                    return "Nothing";

                case "/-/":
                    _parent.setReceiver("AUTO_N");
                    _parent.Shutdown();
                    return "Nothing";

                default:
                    return "Nothing";
            }                
        }
    }
}
