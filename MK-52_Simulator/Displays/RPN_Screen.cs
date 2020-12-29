using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator.Displays
{
    //
    // Implements the generic interface to calculator display
    //
    public class RPN_Screen
    {
        protected RPN_Calculator _parent = null;

        public RPN_Screen(RPN_Calculator parent)
        {
            _parent = parent;
        }

        public virtual void setScreenValues(string[] screenValues)
        {
        }

        protected virtual void makeStatus(string[] screenValues)
        {
            StringBuilder sb = new StringBuilder();
            screenValues[0] = screenValues[0].PadLeft(RPN_Display.StatusWidth);
        }
    }
 }
