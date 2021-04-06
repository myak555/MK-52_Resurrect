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
    // Implements a receiver for F-modified buttons
    //
    public class Receiver_AUTO_F : Receiver_AUTO
    {
        public Receiver_AUTO_F(MK52_Host parent)
            : base(parent)
        {
            Moniker = "AUTO_F";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE(" F ");
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
                case 2:
                    return _rpnf.requestNextReceiver("AUTO_FK");
                case 3:
                    return _rpnf.requestNextReceiver("AUTO_FA");
                case 4:
                    _parent._m_RPN_Stack.toggleAngleMode();
                    return base.tick(0);

                // Column 1 does nothing (for now)
                case 5:
                case 6:
                case 7:
                case 8:

                // Column 2 does nothing (for now)
                case 9:
                case 10:
                case 11:
                case 12:
                    return 0;

                // Column 3
                case 13:
                    _rpnf.execute(RPN_Functions.FUNC_SIN);
                    break;
                case 14:
                    _rpnf.execute(RPN_Functions.FUNC_ARCSIN);
                    break;
                case 15:
                    _rpnf.execute(RPN_Functions.FUNC_EXP);
                    break;
                case 16:
                    _rpnf.execute(RPN_Functions.FUNC_10X);
                    break;

                // Column 4
                case 17:
                    _rpnf.execute(RPN_Functions.FUNC_COS);
                    break;
                case 18:
                    _rpnf.execute(RPN_Functions.FUNC_ARCCOS);
                    break;
                case 19:
                    _rpnf.execute(RPN_Functions.FUNC_LG);
                    break;
                case 20:
                    _rpnf.execute(RPN_Functions.FUNC_ROT);
                    break;

                // Column 5
                case 21:
                    _rpnf.execute(RPN_Functions.FUNC_TG);
                    break;
                case 22:
                    _rpnf.execute(RPN_Functions.FUNC_ARCTG);
                    break;
                case 23:
                    _rpnf.execute(RPN_Functions.FUNC_LN);
                    break;
                case 24:
                    // AUTO is already on
                    break;

                // Column 6
                case 25:
                    _rpnf.execute(RPN_Functions.FUNC_SQRT);
                    break;
                case 26:
                    _rpnf.execute(RPN_Functions.FUNC_PI);
                    break;
                case 27:
                    _rpnf.execute(RPN_Functions.FUNC_POW);
                    break;
                case 28:
                    return _rpnf.requestNextReceiver("PROG_N");

                // Column 7
                case 29:
                    _rpnf.execute(RPN_Functions.FUNC_1X);
                    break;
                case 30:
                    _rpnf.execute(RPN_Functions.FUNC_X2);
                    break;
                case 31:
                    _rpnf.execute(RPN_Functions.FUNC_BX);
                    break;
                case 32:
                    // Clear F mode
                    break;
                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("AUTO_N");
                    return 33;
                default: // all other buttons do nothing, keeping F-mode
                    return 0;
            }
            return _rpnf.requestNextReceiver("AUTO_N");
        }
    }
}
