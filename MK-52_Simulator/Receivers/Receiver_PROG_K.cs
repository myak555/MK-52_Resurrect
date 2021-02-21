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
    // Implements a generic empty receiver
    //
    public class Receiver_PROG_K: Receiver_PROG
    {
        public Receiver_PROG_K(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_K";
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
                    _rpnf.requestNextReceiver("PROG_F");
                    return 0;
                case 3:
                    _rpnf.requestNextReceiver("PROG_A");
                    return 0;
                case 4:
                    _rpnf.execute(RPN_Functions.FUNC_TOGGLE_EMOD, "");
                    return base.tick(0);

                // Column 1
                case 5:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTLTY);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 6:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTEQY);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 7:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTGEY);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;
                case 8:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IFNOTNEY);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N", 0);
                    return 0;

                // Column 2
                case 9:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_K_M2X);
                    _rpnf.requestNextReceiver("REGISTER", "PROG_N", 0);
                    return 0;
                case 10:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_K_X2M);
                    _rpnf.requestNextReceiver("REGISTER", "PROG_N", 0);
                    return 0;
                case 11:
                    _rpnf.progMem.updateLine_P("# K-GOTO is bad!");
                    break;
                case 12:
                    _rpnf.progMem.updateLine_P("# K-GOSUB is bad!");
                    break;

                // Column 3
                case 13:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_WHOLE);
                    break;
                case 14:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_ABS);
                    break;
                case 15:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_EE);
                    break;
                case 16:
                    _rpnf.progMem.commentLine();
                    break;

                // Column 4
                case 17:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_FRAC);
                    break;
                case 18:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_SIGN);
                    break;
                case 19:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LOG);
                    break;
                case 20:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_AND);
                    break;

                // Column 5
                case 21:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_MAX);
                    break;
                case 22:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_DM2D);
                    break;
                case 23:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_DMS2D);
                    break;
                case 24:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_OR);
                    break;

                // Column 6
                case 25:
                    // TODO
                    _rpnf.progMem.updateLine_P("#K-SQRT");
                    break;
                case 26:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_D2DM);
                    break;
                case 27:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_D2DMS);
                    break;
                case 28:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_XOR);
                    break;

                // Column 7
                case 29:
                    // TODO
                    _rpnf.progMem.updateLine_P("#K-1/X");
                    break;
                case 30:
                    // TODO
                    _rpnf.progMem.updateLine_P("#K-X^2");
                    break;
                case 31:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_RAND);
                    break;
                case 32:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_NOT);
                    break;

                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("PROG_N");
                    return 33;
                default: // all other buttons do nothing, keeping K-mode
                    return 0;
            }
            _rpnf.execute(RPN_Functions.FUNC_INCREMENT_PC);
            _rpnf.requestNextReceiver("PROG_N");
            return 0;
        }
    }
}
