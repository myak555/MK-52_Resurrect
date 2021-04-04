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
    // Implements a generic receiver for all keys in auto mode
    //
    public class Receiver_AUTO_N : Receiver_AUTO
    {
        public Receiver_AUTO_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "AUTO_N";
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            switch( scancode)
            {
                case 0: // keyboard inactive
                    return base.tick(0);

                // Column 0
                case 1:
                    return _rpnf.requestNextReceiver("AUTO_F");
                case 2:
                    return _rpnf.requestNextReceiver("AUTO_K");
                case 3:
                    return _rpnf.requestNextReceiver("AUTO_A");
                case 4:
                    _parent._m_RPN_Stack.toggleAngleMode();
                    break;

                // Column 1
                case 5:
                    _rpnf.progMem.incrementCounter();
                    break;
                case 6:
                    _rpnf.progMem.decrementCounter();
                    break;
                case 7:
                    _rpnf.progMem.resetCounter();
                    break;
                case 8:
                    return _rpnf.requestNextReceiver("AUTO_R");

                // Column 2
                case 9:
                    return _rpnf.requestNextReceiver("REGISTER_MX");
                case 10:
                    return _rpnf.requestNextReceiver("REGISTER_XM");
                case 11:
                    return _rpnf.requestNextReceiver("ADDRESS_PC");
                case 12:
                    _rpnf.executeStep();
                    break;

                // Column 5
                case 24:
                    _rpnf.execute(RPN_Functions.FUNC_NEGATE);
                    break;

                // Column 6
                case 25:
                    _rpnf.execute(RPN_Functions.FUNC_MINUS);
                    break;
                case 26:
                    _rpnf.execute(RPN_Functions.FUNC_PLUS);
                    break;
                case 27:
                    _rpnf.execute(RPN_Functions.FUNC_SWAP);
                    break;

                // Column 7
                case 29:
                    _rpnf.execute(RPN_Functions.FUNC_DIVIDE);
                    break;
                case 30:
                    _rpnf.execute(RPN_Functions.FUNC_MULTIPLY);
                    break;
                case 31:
                    _rpnf.execute(RPN_Functions.FUNC_ENTER);
                    break;
                case 32:
                    if (_parent._m_RPN_Stack.customLabels())
                        _parent._m_RPN_Stack.resetLabels();
                    else _rpnf.execute(RPN_Functions.FUNC_CLEAR_X);
                    break;
                case 33:
                    return _rpnf.requestNextReceiver("OFF");

                default: // all other buttons activate number entry
                    _rpnf.execute(RPN_Functions.FUNC_ENTER);
                    base.tick(0); // redraw stack movement
                    _rpnf.requestNextReceiver("NUMBER");
                    return scancode;
            }
            return base.tick(0);
        }
    }
}
