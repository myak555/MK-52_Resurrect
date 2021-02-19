//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    //
    // Implements a receiver for A-modified buttons
    //
    public class Receiver_AUTO_A : Receiver_AUTO
    {
        public Receiver_AUTO_A(MK52_Host parent)
            : base(parent)
        {
            Moniker = "AUTO_A";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" A ");
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            switch (scancode)
            {
                case 0: // keyboard inactive
                    return 0;

                // Column 0
                case 1:
                    _rpnf.requestNextReceiver("AUTO_F");
                    return 0;
                case 2:
                    _rpnf.requestNextReceiver("AUTO_K");
                    return 0;
                case 4:
                    _rpnf.execute(RPN_Functions.FUNC_TOGGLE_DMOD, "");
                    base.tick(0);
                    return 0;

                // Column 1
                case 5:
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;
                case 6:
                    _rpnf.execute(RPN_Functions.FUNC_DECREMENT_MC);
                    break;
                case 7:
                    _rpnf.execute(RPN_Functions.FUNC_RESET_MC);
                    break;
                case 8:
                    return 0;

                // Column 2
                case 9:
                    _rpnf.requestNextReceiver("ADDRESS_AMX");
                    return 0;
                case 10:
                    _rpnf.requestNextReceiver("ADDRESS_AXM");
                    return 0;
                case 11:
                    _rpnf.requestNextReceiver("ADDRESS_MC", "AUTO_N", 0);
                    return 0;
                case 12:
                    _rpnf.execute(RPN_Functions.FUNC_A_M2X);
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;

                // Column 3 does nothing
                // Column 4 does nothing

                // Column 5
                case 22:
                    _rpnf.execute(RPN_Functions.FUNC_D2RAD);
                    break;
                case 23:
                    _rpnf.execute(RPN_Functions.FUNC_MM2IN);
                    break;
                case 24:
                    _rpnf.requestNextReceiver("FILE_N");
                    return 0;

                // Column 6
                case 25:
                    // TODO
                    _parent._m_RPN_Stack.setStackLabel_P(0, "A-SQRT is available!");
                    break;
                case 26:
                    _rpnf.execute(RPN_Functions.FUNC_RAD2D);
                    break;
                case 27:
                    _rpnf.execute(RPN_Functions.FUNC_IN2MM);
                    break;
                case 28:
                    // TODO
                    _rpnf.requestNextReceiver("DATA");
                    return 0;

                // Column 7
                case 29:
                    // TODO
                    _parent._m_RPN_Stack.setStackLabel_P(0, "A-1/X is available!");
                    break;
                case 30:
                    // TODO
                    _parent._m_RPN_Stack.setStackLabel_P(0, "A-X2 is available!");
                    break;
                case 31:
                    _rpnf.execute(RPN_Functions.FUNC_SEED);
                    break;
                case 32:
                    _rpnf.requestNextReceiver("OFF");
                    return 0;
                default: // all other buttons do nothing, keeping A-mode
                    return 0;
            }
            _rpnf.requestNextReceiver("AUTO_N");
            return 0;
        }
    }
}
