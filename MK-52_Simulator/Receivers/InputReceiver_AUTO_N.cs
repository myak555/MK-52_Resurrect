using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic receiver for all keys in auto mode
    //
    public class InputReceiver_AUTO_N: RPN_InputReceiver
    {
        public InputReceiver_AUTO_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_N";
        }

        public override string tick(RPN_Button button)
        {
            if (_parent.Program.Counter.isActive)
            {
                _parent.Program.Counter.onButton(button, true);
                return "Nothing";
            }
            if (_parent.Registers.isActive)
            {
                _parent.Registers.onButton(button);
                return "Nothing";
            }
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    return "AUTO_F";
                case "Func K":
                    return "AUTO_K";
                case "Func A":
                    return "AUTO_A";
                case "Mode":
                    _parent.SwapDegreeMode();
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
                    _parent.CallStack.Clear();
                    return "Nothing";
                case "S/P":
                    if (_parent.Program.isAtStop)
                        _parent.Program.Counter.Increment();
                    _parent.setReceiver("AUTO_R");
                    return "Nothing";

                // Column 2
                case "M->X":
                    _parent.Registers.ActivateEntry( RPN_Registers.RegisterToStack);
                    return "Nothing";
                case "X->M":
                    _parent.Registers.ActivateEntry(RPN_Registers.StackToRegister);
                    return "Nothing";
                case "GOTO":
                    _parent.Program.Counter.ActivateEntry();
                    return "Nothing";
                case "GOSUB":
                    if (_parent.Program.isAtStop && _parent.CalcStack.X_Label.StartsWith("STOP"))
                    {
                        _parent.CalcStack.X_Label = "X:";
                        _parent.Program.Counter.Increment();
                        return "Nothing";
                    }
                    _parent.Program.ExecuteCurrentLine();
                    if (_parent.Program.isAtStop)
                        _parent.CalcStack.X_Label = "STOP reached";
                    return "Nothing";
                default:
                    _parent.CalcStack.onButton(button);
                    return "Nothing";
            }                
        }

        public override string DisplayName
        {
            get
            {
                if (_parent.CalcStack.isActive) return "NUM";
                if (_parent.Program.Counter.isActive) return "PC?";
                if (_parent.Registers.isActive) return "RG?";
                return _displayName;
            }
        }
    }
}
