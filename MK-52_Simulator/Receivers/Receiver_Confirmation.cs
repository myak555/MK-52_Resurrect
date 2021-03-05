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

namespace MK52Simulator
{
    //
    // Implements a text data entry editor
    //
    public class Receiver_Confirmation : Receiver
    {   
        protected string _Question =  "Confirm? (\u0018)";

        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_Confirmation(MK52_Host parent)
            : base(parent)
        {
            Moniker = "Confirm";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent._m_Hardware_LCD;
            lm.outputTerminalLine(LCD_Manager.SCREEN_ROWS-2, _Question);
            lm.forcePaint();
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            switch( scancode)
            {
                case 0:
                    return 0;
                case 31:
                    performAction();
                    _rpnf.requestNextReceiver(_return_to);
                    return 0;
                case 33:
                    _rpnf.requestNextReceiver(_return_to);
                    return 33;
                default:
                    break;
            }
            _rpnf.requestNextReceiver(_return_to);
            return 0;
        }

        protected virtual void performAction()
        {
        }
    }
}
