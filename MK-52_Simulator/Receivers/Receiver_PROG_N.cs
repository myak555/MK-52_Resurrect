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
    public class Receiver_PROG_N : Receiver_PROG
    {
        public Receiver_PROG_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "PROG_N";
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            switch (scancode)
            {
                case 0: // keyboard inactive
                    return base.tick(0);

                // Column 0
                case 1:
                    _rpnf.requestNextReceiver("PROG_F");
                    return 0;
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
                    break;
                case 6:
                    _rpnf.execute(RPN_Functions.FUNC_DECREMENT_PC);
                    return base.tick(0);
                case 7:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_RETURN);
                    break;
                case 8:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_STOP);
                    break;

                // Column 2
                case 9:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_M2X);
                    _rpnf.requestNextReceiver("REGISTER");
                    return 0;
                case 10:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_X2M);
                    _rpnf.requestNextReceiver("REGISTER");
                    return 0;
                case 11:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_GOTO);
                    _rpnf.requestNextReceiver("ADDRESS");
                    return 0;
                case 12:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_GOSUB);
                    _rpnf.requestNextReceiver("ADDRESS");
                    return 0;

                // Column 5
                case 24:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_NEGATE);
                    break;

                // Column 6
                case 25:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_MINUS);
                    break;
                case 26:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_PLUS);
                    break;
                case 27:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_SWAP);
                    break;

                // Column 7
                case 29:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_DIVIDE);
                    break;
                case 30:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_MULTIPLY);
                    break;
                case 31:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_ENTER);
                    break;
                case 32:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_CLEAR_X);
                    break;
                case 33:
                    _rpnf.requestNextReceiver("OFF");
                    return 0;

                default: // all other buttons activate number entry
                    _rpnf.requestNextReceiver("NUMBER_PROG");
                    return scancode;
            }
            _rpnf.execute(RPN_Functions.FUNC_INCREMENT_PC);
            return base.tick(0);
        }
    }
}
