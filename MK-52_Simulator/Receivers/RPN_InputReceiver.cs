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
    public class RPN_InputReceiver
    {
        public string Moniker = "";
        public RPN_Screen Display = null;
        public string DisplayName = "   ";

        protected RPN_Calculator _parent;
        protected string _partial = "";

        public RPN_InputReceiver(RPN_Calculator parent, RPN_Screen display)
        {
            _parent = parent;
            Display = display;
        }

        public virtual void onButton(RPN_Button button)
        {
            return;
        }

        public virtual void onSet()
        {
            return;
        }
    }
}
