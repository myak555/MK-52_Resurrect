using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic receiver for all keys in auto mode
    //
    public class InputReceiver_AUTO_N: RPN_InputReceiver
    {
        public InputReceiver_AUTO_N(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_N";
        }

        public override void onButton(RPN_Button button)
        {
            if (_parent.Program.isAddressEntry)
            {
                _parent.Program.AddDigitToAddress(button.Moniker);
                return;
            }
            if (_parent.Registers.isAddressEntry)
            {
                _parent.Registers.AddDigitToAddress(button.Register);
                return;
            }
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("AUTO_F");
                    return;
                case "Func K":
                    _parent.setReceiver("AUTO_K");
                    return;
                case "Func A":
                    _parent.setReceiver("AUTO_A");
                    return;
                case "Mode":
                    _parent.SwapDegreeMode();
                    return;

                // Column 1
                case "->":
                    _parent.Program.Counter.Increment();
                    return;
                case "<-":
                    _parent.Program.Counter.Decrement();
                    return;
                case "B/O":
                    _parent.Program.Counter.Set(0);
                    _parent.CallStack.Clear();
                    return;
                case "S/P":
                    if (_parent.Program.isAtStop)
                        _parent.Program.Counter.Increment();
                    _parent.setReceiver("AUTO_R");
                    return;

                // Column 2
                case "M->X":
                    _parent.Registers.ActivateEntry( RPN_Registers.RegisterToStack);
                    return;
                case "X->M":
                    _parent.Registers.ActivateEntry(RPN_Registers.StackToRegister);
                    return;
                case "GOTO":
                    _parent.Program.Counter.ActivateEntry();
                    return;
                case "GOSUB":
                    if (_parent.Program.isAtStop && _parent.CalcStack.X_Label.StartsWith("STOP"))
                    {
                        _parent.CalcStack.X_Label = "X:";
                        _parent.Program.Counter.Increment();
                        return;
                    }
                    _parent.Program.ExecuteCurrentLine();
                    if (_parent.Program.isAtStop)
                        _parent.CalcStack.X_Label = "STOP reached";
                    return;
                default:
                    _parent.CalcStack.onButton(button.Moniker);
                    return;
            }                
        }
    }
}
