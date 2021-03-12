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
    public class Receiver_PROG_A: Receiver_PROG
    {
        public Receiver_PROG_A(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_A";
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
                    _rpnf.requestNextReceiver("PROG_F");
                    return 0;
                case 2:
                    _rpnf.requestNextReceiver("PROG_K");
                    return 0;
                case 4:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_SET_DMOD_GRD);
                    break;

                // Column 1
                case 5:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LBT);
                    _rpnf.requestNextReceiver("TEXT", "PROG_N");
                    return 0;
                case 6:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LBZ);
                    _rpnf.requestNextReceiver("TEXT", "PROG_N");
                    return 0;
                case 7:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LBY);
                    _rpnf.requestNextReceiver("TEXT", "PROG_N");
                    return 0;
                case 8:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LBX);
                    _rpnf.requestNextReceiver("TEXT", "PROG_N");
                    return 0;

                // Column 2
                case 9:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_A_M2X);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N");
                    return 0;
                case 10:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_A_X2M);
                    _rpnf.requestNextReceiver("ADDRESS", "PROG_N");
                    return 0;
                case 11:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_LBR);
                    break;
                case 12:
                    _rpnf.progMem.deleteLine();
                    break;

                // Column 3
                case 16:
                    _rpnf.progMem.commentLine();
                    _rpnf.requestNextReceiver("TEXT", "PROG_N");
                    return 0;

                // Column 5
                case 22:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_D2RAD);
                    break;
                case 23:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_MM2IN);
                    break;
                case 24:
                    _rpnf.requestNextReceiver("FILE_N");
                    return 0;

                // Column 6
                case 26:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_RAD2D);
                    break;
                case 27:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_IN2MM);
                    break;
                case 28:
                    _rpnf.requestNextReceiver("DATA_N");
                    return 0;

                // Column 7
                case 31:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_SEED);
                    break;
                case 32:
                case 33:
                    _rpnf.requestNextReceiver("PROG_N");
                    return 33;
                default: // all other buttons do nothing, keeping A-mode
                    return 0;
            }
            _rpnf.execute(RPN_Functions.FUNC_INCREMENT_PC);
            _rpnf.requestNextReceiver("PROG_N");
            return 0;
        }
    }
}
