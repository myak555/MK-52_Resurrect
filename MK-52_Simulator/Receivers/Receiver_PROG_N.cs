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
                    return _rpnf.requestNextReceiver("PROG_F");
                case 2:
                    return _rpnf.requestNextReceiver("PROG_K");
                case 3:
                    return _rpnf.requestNextReceiver("PROG_A");
                case 4:
                    _parent._m_Program_Memory.toggleEditMode();
                    return base.tick(0);

                // Column 1
                case 5:
                    break;
                case 6:
                    _rpnf.progMem.decrementCounter();
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
                    return _rpnf.requestNextReceiver("REGISTER");
                case 10:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_X2M);
                    return _rpnf.requestNextReceiver("REGISTER");
                case 11:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_GOTO);
                    return _rpnf.requestNextReceiver("ADDRESS");
                case 12:
                    _rpnf.appendProgramLine_P(RPN_Functions.FUNC_GOSUB);
                    return _rpnf.requestNextReceiver("ADDRESS");

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
                    return _rpnf.requestNextReceiver("OFF");

                default: // all other buttons activate number entry
                    _rpnf.requestNextReceiver("NUMBER_PROG");
                    return scancode;
            }
            _rpnf.progMem.incrementCounter();
            return base.tick(0);
        }
    }
}
