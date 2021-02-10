using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic empty receiver that stops execution at S/P button
    //
    public class InputReceiver_RUN: RPN_InputReceiver
    {
        public InputReceiver_RUN(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_R";
            _displayName = "RUN";
        }

        public override string tick(RPN_Button button)
        {
            switch (button.Moniker)
            {
                // Column 1
                case "S/P":
                    _parent.setReceiver("AUTO_N");
                    return "Nothing";
                default:
                    _parent.Program.ExecuteCurrentLine();
                    return "Nothing";
            }                
        }
    }
}
