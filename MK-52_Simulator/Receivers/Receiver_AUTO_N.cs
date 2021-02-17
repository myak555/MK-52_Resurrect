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

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent._m_RPN_Functions;
            switch( scancode)
            {
                case 0: // keyboard inactive
                    return 0;

                // Column 0
                case 1:
                    _parent.setReceiver("AUTO_F");
                    return 0;
                case 2:
                    _parent.setReceiver("AUTO_K");
                    return 0;
                case 3:
                    _parent.setReceiver("AUTO_A");
                    return 0;
                case 4:
                    _rpnf.execute(RPN_Functions.FUNC_TOGGLE_DMOD, "");
                    break;

                // Column 1
                case 5:
                    _rpnf.execute(RPN_Functions.FUNC_INCREMENT_PC);
                    break;
                case 6:
                    _rpnf.execute(RPN_Functions.FUNC_DECREMENT_PC);
                    break;
                case 7:
                    _rpnf.execute(RPN_Functions.FUNC_RESET_PC);
                    break;
                case 8:
                    _parent.setReceiver("AUTO_R");
                    return 0;

                //// Column 2
                //case 9:
                //    _mode = 3;
                //    _rr->activate(0, 0);
                //    break;
                //case 10:
                //    _mode = 4;
                //    _rr->activate(0, 0);
                //    break;
                //case 11:
                //    _mode = 5;
                //    _ar->activate(0, 0);
                //    _lcd->updateStatusPC( _ar->toString());
                //    break;
                case 12:
                    _rpnf.executeStep();
                    //_lcd->updateStatusPC( _rpnf->progMem->getCounter());
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
                    if (_parent._m_RPN_Stack.customStackLabels())
                        _parent._m_RPN_Stack.resetStackLabels();
                    else _rpnf.execute(RPN_Functions.FUNC_CLEAR_X);
                    break;

                default: // all other buttons activate number entry
                    _rpnf.execute(RPN_Functions.FUNC_ENTER);
                    base.tick(0); // redraw stack movement
                    _parent.setReceiver("NUMBER");
                    return scancode;
            }
            return base.tick(0);
        }
    }
}
