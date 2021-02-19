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
    // Implements a receiver for K-modified buttons
    //
    public class Receiver_AUTO_K : Receiver_AUTO
    {
        public Receiver_AUTO_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_K";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" K ");
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
                case 3:
                    _rpnf.requestNextReceiver("AUTO_A");
                    return 0;
                case 4:
                    _rpnf.execute(RPN_Functions.FUNC_TOGGLE_DMOD, "");
                    base.tick(0);
                    return 0;

                // Column 1 does nothing (for now)
                case 5:
                case 6:
                case 7:
                case 8:
                    return 0;

                // Column 2
                case 9:
                    _rpnf.requestNextReceiver("REGISTER_A", "AUTO_N", Receiver_Register_A._KMX);
                    return 0;
                case 10:
                    _rpnf.requestNextReceiver("REGISTER_A", "AUTO_N", Receiver_Register_A._KXM);
                    return 0;
                case 11:
                    _parent._m_RPN_Stack.setStackLabel_P(0, "K-GOTO is bad for you!");
                    break;
                case 12:
                    _parent._m_RPN_Stack.setStackLabel_P(0, "K-GOSUB is bad for you!");
                    break;

                // Column 3
                case 13:
                    _rpnf.execute(RPN_Functions.FUNC_WHOLE);
                    break;
                case 14:
                    _rpnf.execute(RPN_Functions.FUNC_ABS);
                    break;
                case 15:
                    _rpnf.execute(RPN_Functions.FUNC_EE);
                    break;
                case 16:
                    // NOP
                    break;

                // Column 4
                case 17:
                    _rpnf.execute(RPN_Functions.FUNC_FRAC);
                    break;
                case 18:
                    _rpnf.execute(RPN_Functions.FUNC_SIGN);
                    break;
                case 19:
                    _rpnf.execute(RPN_Functions.FUNC_LOG);
                    break;
                case 20:
                    _rpnf.execute(RPN_Functions.FUNC_AND);
                    break;

                // Column 5
                case 21:
                    _rpnf.execute(RPN_Functions.FUNC_MAX);
                    break;
                case 22:
                    _rpnf.execute(RPN_Functions.FUNC_DM2D);
                    break;
                case 23:
                    _rpnf.execute(RPN_Functions.FUNC_DMS2D);
                    break;
                case 24:
                    _rpnf.execute(RPN_Functions.FUNC_OR);
                    break;

                // Column 6
                case 25:
                    // TODO
                    //_rpnf.execute(RPN_Functions.FUNC_SQRT);
                    _parent._m_RPN_Stack.setStackLabel_P(0, "K-SQRT is available!");
                    break;
                case 26:
                    _rpnf.execute(RPN_Functions.FUNC_D2DM);
                    break;
                case 27:
                    _rpnf.execute(RPN_Functions.FUNC_D2DMS);
                    break;
                case 28:
                    _rpnf.execute(RPN_Functions.FUNC_XOR);
                    return 0;

                // Column 7
                case 29:
                    // TODO
                    //_rpnf.execute(RPN_Functions.FUNC_1X);
                    _parent._m_RPN_Stack.setStackLabel_P(0, "K-1/X is available!");
                    break;
                case 30:
                    // TODO
                    //_rpnf.execute(RPN_Functions.FUNC_X2);
                    _parent._m_RPN_Stack.setStackLabel_P(0, "K-X2 is available!");
                    break;
                case 31:
                    _rpnf.execute(RPN_Functions.FUNC_RAND);
                    break;
                case 32:
                    _rpnf.execute(RPN_Functions.FUNC_NOT);
                    break;
                default: // all other buttons do nothing, keeping K-mode
                    return 0;
            }
            _rpnf.requestNextReceiver("AUTO_N");
            return 0;
        }
    }
}
