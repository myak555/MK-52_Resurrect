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

        //public string[] fModeLabels = { "[     ] ",
        //                                "[  F  ] ",
        //                                "[  K  ] ",
        //                                "[  A  ] ",
        //                                "[M->X_] ",
        //                                "[_X->M] ",
        //                                "[KM->X] ",
        //                                "[KX->M] ",
        //                                "[AM->X] ",
        //                                "[AX->M] ",
        //                                "[PRG->] ",
        //                                "[MEM->] "};

        public RPN_Screen(RPN_Calculator parent)
        {
            _parent = parent;
        }

        public virtual void setScreenValues(string[] screenValues)
        {
        }

        protected virtual void makeStatus(string[] screenValues)
        {
            StringBuilder sb = new StringBuilder(screenValues[0]);
            sb.Append("[");
            sb.Append(_parent.CurrentReceiver.DisplayName);
            sb.Append("] ");
            screenValues[0] = sb.ToString().PadLeft(RPN_Display.StatusWidth);
        }
    }
 }
