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
    public class InputReceiver_PROG_N: RPN_InputReceiver
    {
        public InputReceiver_PROG_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_N";
        }

        public override string tick(RPN_Button button)
        {
            if ( _parent.Program.Number.isActive)
            {
                if (button.Moniker != "Enter")
                {
                    _parent.Program.Number.tick(button);
                    return "Nothing";
                }
                _parent.Program.SetCurrentLine( _parent.Program.Number.ToString().Trim());
                _parent.Program.Counter.Increment();
                _parent.Program.Number.Clear();
                return "Nothing";
            }
            if (_parent.Program.Counter.isActive)
            {

                if (_parent.Program.Counter.onButton(button, false))
                {
                    _parent.Program.AppendCounterString();
                    _parent.Program.Counter.Increment();
                }
                return "Nothing";
            }
            if (_parent.Registers.isActive)
            {

                if (_parent.Registers.onButton(button))
                {
                    _parent.Registers.AppendRegisterString();
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
                case "Func A":
                    _parent.setReceiver("PROG_A");
                    return "Nothing";

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    return "Nothing";
                case "<-":
                    _parent.Program.Counter.Decrement();
                    return "Nothing";
                case "B/O":
                    _parent.Program.SetCurrentLine( "RETURN");
                    _parent.Program.Counter.Increment();
                    return "Nothing";
                case "S/P":
                    _parent.Program.SetCurrentLine("STOP");
                    _parent.Program.Counter.Increment();
                    return "Nothing";

                // Column 2
                case "M->X":
                    _parent.Program.SetCurrentLine("M->X ");
                    _parent.Registers.ActivateEntry( RPN_Registers.None);
                    return "Nothing";
                case "X->M":
                    _parent.Program.SetCurrentLine("X->M ");
                    _parent.Registers.ActivateEntry( RPN_Registers.None);
                    return "Nothing";
                case "GOTO":
                    _parent.Program.SetCurrentLine("GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return "Nothing";
                case "GOSUB":
                    _parent.Program.SetCurrentLine("GOSUB ");
                    _parent.Program.Counter.ActivateEntry();
                    return "Nothing";

                // Number entry (columns 3-5)
                case "0":
                case "1":
                case "2":
                case "3":
                case "4":
                case "5":
                case "6":
                case "7":
                case "8":
                case "9":
                case ".":
                case "EE":
                    _parent.Program.Number.tick(button);
                    return "Nothing";

                // Operations
                default:
                    _parent.Program.SetCurrentLine( button.Moniker);
                    _parent.Program.Counter.Increment();
                    return "Nothing";
            }            
        }

        public override string DisplayName
        {
            get
            {
                if (_parent.Program.Number.isActive) return _parent.Program.Number.DisplayName;
                if (_parent.Program.Counter.isActive) return "PC?";
                if (_parent.Registers.isActive) return "RG?";
                return _displayName;
            }
        }
    }
}
