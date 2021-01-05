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
            if ( _parent.Program.Number.isActive)
            {
                if (button.Moniker != "Enter")
                {
                    _parent.Program.Number.onButton(button);
                    return;
                }
                _parent.Program.SetCurrentLine( _parent.Program.Number.ToString().Trim());
                _parent.Program.Counter.Increment();
                _parent.Program.Number.Clear();
                return;
            }
            if (_parent.Program.Counter.isActive)
            {

                if (_parent.Program.Counter.onButton(button, false))
                {
                    _parent.Program.AppendCounterString();
                    _parent.Program.Counter.Increment();
                }
                return;
            }
            if (_parent.Registers.isActive)
            {

                if (_parent.Registers.onButton(button))
                {
                    _parent.Registers.AppendRegisterString();
                    _parent.Program.Counter.Increment();
                }
                return;
            }
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
                    _parent.Program.SetCurrentLine( "RETURN");
                    _parent.Program.Counter.Increment();
                    return;
                case "S/P":
                    _parent.Program.SetCurrentLine("STOP");
                    _parent.Program.Counter.Increment();
                    return;

                // Column 2
                case "M->X":
                    _parent.Program.SetCurrentLine("M->X ");
                    _parent.Registers.ActivateEntry( RPN_Registers.None);
                    return;
                case "X->M":
                    _parent.Program.SetCurrentLine("X->M ");
                    _parent.Registers.ActivateEntry( RPN_Registers.None);
                    return;
                case "GOTO":
                    _parent.Program.SetCurrentLine("GOTO ");
                    _parent.Program.Counter.ActivateEntry();
                    return;
                case "GOSUB":
                    _parent.Program.SetCurrentLine("GOSUB ");
                    _parent.Program.Counter.ActivateEntry();
                    return;

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
                    _parent.Program.Number.onButton(button); 
                    return;

                // Operations
                default:
                    _parent.Program.SetCurrentLine( button.Moniker);
                    _parent.Program.Counter.Increment();
                    return;
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
