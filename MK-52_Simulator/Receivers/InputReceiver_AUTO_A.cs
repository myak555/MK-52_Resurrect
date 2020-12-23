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
    public class InputReceiver_AUTO_A: RPN_InputReceiver
    {
        public InputReceiver_AUTO_A(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_A";
            DisplayName = "  A  ";
        }

        public override bool onButton(RPN_Button button)
        {
            if (_parent.Memory.isAddressEntry)
            {
                _parent.Memory.AddDigitToAddress(button.Moniker);
                return true;
            }
            switch (button.Moniker)
            {
                // Column 0
                case "Func F":
                    _parent.setReceiver("AUTO_F");
                    return true;
                case "Func K":
                    _parent.setReceiver("AUTO_K");
                    return true;
                case "Mode":
                    _parent.SwapDegreeMode();
                    return true;

                // Column 1
                case "->":
                    _parent.Memory.Counter.Increment();
                    return true;
                case "<-":
                    _parent.Memory.Counter.Decrement();
                    return true;
                case "B/O":
                    _parent.Memory.Counter.Set(0);
                    return true;

                // Column 2
                case "M->X":
                    _parent.Memory.ActivateEntry( RPN_Memory.MemoryToStack);
                    return true;
                case "X->M":
                    _parent.Memory.ActivateEntry(RPN_Memory.StackToMemory);
                    return true;
                case "GOTO":
                    _parent.Memory.Counter.ActivateEntry();
                    return true;

                // Column 3
                // Does nothing

                // Column 4
                // Does nothing

                // Column 5
                case "6":
                    _parent.executeFunction("<-RAD");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "3":
                    _parent.executeFunction("<-IN");
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 6
                case "+":
                    _parent.executeFunction("RAD->");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Swap":
                    _parent.executeFunction("IN->");
                    _parent.setReceiver("AUTO_N");
                    return true;

                // Column 7
                case "Enter":
                    _parent.executeFunction("SEED");
                    _parent.setReceiver("AUTO_N");
                    return true;
                case "Cx":
                    _parent.Stack.CompleteEntry();
                    _parent.setReceiver("AUTO_N");
                    _parent.Shutdown();
                    return true;
                default:
                    return false;
            }                
        }
    }
}
