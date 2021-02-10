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
    public class InputReceiver_PROG_A: RPN_InputReceiver
    {
        public InputReceiver_PROG_A(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_A";
            _displayName = " A ";
        }

        public override string tick(RPN_Button button)
        {
            if (_parent.Program.Text.isActive)
            {
                _parent.Program.Text.tick(button);
                if (!_parent.Program.Text.isActive)
                {
                    _parent.Program.AppendCurrentLine(_parent.Program.Text.EntryText);
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("PROG_N");
                }
                return "Nothing";
            }
            if (_parent.Memory.Counter.isActive)
            {

                if (_parent.Memory.Counter.onButton(button, false))
                {
                    _parent.Program.AppendCurrentLine(_parent.Memory.Counter.entryResult.ToString("000"));
                    _parent.Program.Counter.Increment();
                }
                return "Nothing";
            }
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("PROG_F");
                    return "Nothing";
                case "Func K":
                    _parent.setReceiver("PROG_K");
                    return "Nothing";
                case "Mode":
                    _parent.Program.SetCurrentLine("GRAD");
                    _parent.Program.Counter.Increment();
                    _parent.setReceiver("PROG_N");
                    return "Nothing";

                // Column 1
                case "->":
                    _parent.Program.SetCurrentLine("LT> ");
                    _parent.Program.Text.ActivateEntry();
                    return "Nothing";
                case "<-":
                    _parent.Program.SetCurrentLine("LZ> ");
                    _parent.Program.Text.ActivateEntry();
                    return "Nothing";
                case "B/O":
                    _parent.Program.SetCurrentLine("LY> ");
                    _parent.Program.Text.ActivateEntry();
                    return "Nothing";
                case "S/P":
                    _parent.Program.SetCurrentLine("LX> ");
                    _parent.Program.Text.ActivateEntry();
                    return "Nothing";

                // Column 2
                case "M->X":
                    _parent.Program.SetCurrentLine("AM->X ");
                    _parent.Memory.Counter.ActivateEntry();
                    return "Nothing";
                case "X->M":
                    _parent.Program.SetCurrentLine("AX->M ");
                    _parent.Memory.Counter.ActivateEntry();
                    return "Nothing";

                // Column 3
                case "1":
                    _parent.Program.SetCurrentLine("e");
                    _parent.Program.Counter.Increment();
                    return "Nothing";

                // Column 5
                case "/-/":
                    _parent.setReceiver("PROG_N");
                    return "Nothing";

                case "EE":
                    _parent.setReceiver("LIST_N");
                    return "Nothing";
                case "Cx":
                    _parent.setReceiver("PROG_N");
                    _parent.Shutdown();
                    return "Nothing";
                default:
                    return "Nothing";
            }                
        }
    }
}
