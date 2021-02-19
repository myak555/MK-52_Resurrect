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
                    _rpnf.requestNextReceiver("DATA_F");
                    return 0;
                case 2:
                    _rpnf.requestNextReceiver("DATA_K");
                    return 0;
                case 3:
                    _rpnf.requestNextReceiver("DATA_A");
                    return 0;
                case 4:
                    _rpnf.execute(RPN_Functions.FUNC_TOGGLE_DMOD, "");
                    break;

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
                    _rpnf.execute(RPN_Functions.FUNC_MEXTOX);
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;

                // Column 2
                case 9:
                    // TODO
                    _rpnf.requestNextReceiver("REGISTER_ME");
                    return 0;
                case 10:
                    // TODO
                    _rpnf.requestNextReceiver("REGISTER_EM");
                    return 0;
                case 11:
                    _rpnf.requestNextReceiver("ADDRESS_MC", "DATA_N", 0);
                    return 0;
                case 12:
                    _rpnf.execute(RPN_Functions.FUNC_XTOMEX);
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;

                // Column 3-5 - number entry

                // Column 6
                case 25:
                case 26:
                    break;
                case 27:
                    _rpnf.execute(RPN_Functions.FUNC_MEMSWP);
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;

                // Column 7
                case 29:
                case 30:
                    break;
                case 31:
                    // TODO
                    _rpnf.execute(RPN_Functions.FUNC_MEMSET,
                        _parent._m_RPN_Stack._DataEntry.ToString().Trim());
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;
                case 32:
                    _rpnf.execute(RPN_Functions.FUNC_MEXCLR);
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_MC);
                    break;

                case 33:
                    // Shutdown signal
                    _rpnf.requestNextReceiver("OFF");
                    return 33;

                default: // all other buttons activate number entry
                    // TODO
                    _rpnf.requestNextReceiver("NUMBER_DATA");
                    return scancode;
            }
            return base.tick(0);
        }
    }
}
