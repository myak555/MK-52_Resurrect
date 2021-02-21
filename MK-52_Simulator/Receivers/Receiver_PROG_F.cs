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
    public class Receiver_PROG_F : Receiver_PROG
    {
        public Receiver_PROG_F(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_F";
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
                    _rpnf.requestNextReceiver("PROG_K");
                    return 0;
                case 3:
                    _rpnf.requestNextReceiver("PROG_A");
                    return 0;
                case 4:
                    _rpnf.execute(RPN_Functions.FUNC_TOGGLE_EMOD, "");
                    return base.tick(0);

                // Column 1
                case 5:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTLT0);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 6:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTEQ0);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 7:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTGE0);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 8:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTNE0);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;

                // Column 2 does nothing (for now)
                case 9:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_L0);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 10:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_L1);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 11:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_L2);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 12:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_L3);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;

                // Column 3
                case 13:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_SIN);
                    break;
                case 14:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_ARCSIN);
                    break;
                case 15:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_EXP);
                    break;
                case 16:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_10X);
                    break;

                // Column 4
                case 17:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_COS);
                    break;
                case 18:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_ARCCOS);
                    break;
                case 19:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LG);
                    break;
                case 20:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_ROT);
                    break;

                // Column 5
                case 21:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_TG);
                    break;
                case 22:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_ARCTG);
                    break;
                case 23:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LN);
                    break;
                case 24:
                    _rpnf.requestNextReceiver("AUTO_N");
                    return 0;

                // Column 6
                case 25:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_SQRT);
                    break;
                case 26:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_PI);
                    break;
                case 27:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_POW);
                    break;
                case 28:
                    // PROG is already on
                    _rpnf.requestNextReceiver("PROG_N");
                    return 0;

                // Column 7
                case 29:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_1X);
                    break;
                case 30:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_X2);
                    break;
                case 31:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_BX);
                    break;
                case 32:
                    // Clear F mode
                    break;
                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("PROG_N");
                    return 33;
                default: // all other buttons do nothing, keeping F-mode
                    return 0;
            }
            _rpnf.execute(RPN_Functions.FUNC_INCREMENT_PC);
            _rpnf.requestNextReceiver("PROG_N");
            return 0;
        }
    }
}
