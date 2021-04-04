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
    public class Receiver_DATA_N: Receiver_DATA
    {
        public Receiver_DATA_N(MK52_Host parent)
            : base( parent)
        {
            Moniker = "DATA_N";
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
                    return _rpnf.requestNextReceiver("DATA_F");
                case 2:
                    return _rpnf.requestNextReceiver("DATA_K");
                case 3:
                    return _rpnf.requestNextReceiver("DATA_A");
                case 4:
                    // TODO: Insert mode
                    //_parent._m_RPN_Stack.toggleAngleMode();
                    // base.tick(0);
                    return 0;

                // Column 1
                case 5:
                    _rpnf.extMem.incrementCounter();
                    break;
                case 6:
                    _rpnf.extMem.decrementCounter();
                    break;
                case 7:
                    _rpnf.extMem.resetCounter();
                    break;
                case 8:
                    _rpnf.execute(RPN_Functions.FUNC_MEXTOX);
                    _rpnf.extMem.incrementCounter();
                    break;

                // Column 2
                case 9:
                    // TODO
                    return _rpnf.requestNextReceiver("REGISTER_ME");
                case 10:
                    // TODO
                    return _rpnf.requestNextReceiver("REGISTER_EM");
                case 11:
                    return _rpnf.requestNextReceiver("ADDRESS_MC", "DATA_N");
                case 12:
                    _rpnf.execute(RPN_Functions.FUNC_XTOMEX);
                    _rpnf.extMem.incrementCounter();
                    break;

                // Column 3-5 - number entry

                // Column 6
                case 25:
                case 26:
                    break;
                case 27:
                    _rpnf.execute(RPN_Functions.FUNC_MEMSWP);
                    _rpnf.extMem.incrementCounter();
                    break;

                // Column 7
                case 29:
                case 30:
                    break;
                case 31:
                    _rpnf.execute(RPN_Functions.FUNC_MEMSET,
                        _parent._m_RPN_Stack._DataEntry.ToString().Trim());
                    _rpnf.extMem.incrementCounter();
                    break;
                case 32:
                    _parent._m_Extended_Memory.clearCurrent();
                    _rpnf.extMem.incrementCounter();
                    break;

                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("OFF");
                    return 33;

                default: // all other buttons activate number entry
                    _rpnf.requestNextReceiver("NUMBER_DATA");
                    return scancode;
            }
            return base.tick(0);
        }
    }
}
