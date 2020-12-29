using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator.Displays;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic empty receiver that stops execution at S/P button
    //
    public class InputReceiver_RUN: RPN_InputReceiver
    {
        public InputReceiver_RUN(RPN_Calculator parent, RPN_Screen display) :
            base( parent, display)
        {
            Moniker = "AUTO_R";
            DisplayName = "RUN";
        }

        public override void onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 1
                case "S/P":
                    _parent.setReceiver("AUTO_N");
                    return;
                default:
                    _parent.Program.ExecuteCurrentLine();
                    return;
            }                
        }
    }
}
