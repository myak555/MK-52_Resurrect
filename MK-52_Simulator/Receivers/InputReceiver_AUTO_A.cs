using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a receiver for A-modified buttons
    //
    public class InputReceiver_AUTO_A: RPN_InputReceiver
    {
        public InputReceiver_AUTO_A(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_A";
            _displayName = " A ";
        }

        public override void onButton(RPN_Button button)
        {
            if (_parent.Memory.Counter.isActive)
            {
                _parent.Memory.onButton(button);
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
                case "Mode":
                    _parent.SwapDegreeMode();
                    return;

                // Column 1
                case "->":
                    _parent.Memory.Counter.Increment();
                    return;
                case "<-":
                    _parent.Memory.Counter.Decrement();
                    return;
                case "B/O":
                    _parent.Memory.Counter.Set(0);
                    return;

                // Column 2
                case "M->X":
                    _parent.Memory.ActivateEntry( RPN_Memory.MemoryToStack);
                    return;
                case "X->M":
                    _parent.Memory.ActivateEntry(RPN_Memory.StackToMemory);
                    return;
                case "GOTO":
                    _parent.Memory.Counter.ActivateEntry();
                    return;

                // Column 3
                // Does nothing

                // Column 4
                // Does nothing

                // Column 5
                case "6":
                    _parent.executeFunction("<-RAD");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "3":
                    _parent.executeFunction("<-IN");
                    _parent.setReceiver("AUTO_N");
                    return;

                // Column 6
                case "+":
                    _parent.executeFunction("RAD->");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "Swap":
                    _parent.executeFunction("IN->");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "EE":
                    _parent.setReceiver("LIST_N");
                    return;

                // Column 7
                case "Enter":
                    _parent.executeFunction("SEED");
                    _parent.setReceiver("AUTO_N");
                    return;
                case "Cx":
                    _parent.CalcStack.CompleteEntry();
                    _parent.setReceiver("AUTO_N");
                    _parent.Shutdown();
                    return;
                default:
                    return;
            }                
        }
    }
}
