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
    // Implements a register entry
    //
    public class Receiver_Register : Receiver
    {        
        private const string _RR_ButtonConversion = "####f####abcd7410852A963B###C#FED";
        
        /// <summary>
        /// Inputs register name into a program line
        /// </summary>
        public Receiver_Register(MK52_Host parent)
            : base( parent)
        {
            Moniker = "REGISTER";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            if (prevReceiver.StartsWith( "PROG"))
                lm.updateTerminalLine(10, _parent._m_Program_Memory.toString());
            lm.updateStatusFMODE( "MEM");
            lm.forcePaint();
            _text = new StringBuilder();
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();  
            char c = _convertButton(_RR_ButtonConversion, scancode);
            switch (c)
            {
                case (char)0:
                    return 0;
                case 'f': // entry completed, action needed
                    _rpnf.requestNextReceiver(_return_to);
                    return scancode;
                case 'a':
                    _text.Append("L0");
                    break;
                case 'b':
                    _text.Append("L1");
                    break;
                case 'c':
                    _text.Append("L2");
                    break;
                case 'd':
                    _text.Append("L3");
                    break;
                default:
                    _text.Append(c);
                    break;
            }
            completeEntry( toString());
            return _rpnf.requestNextReceiver(_return_to);
        }

        protected virtual void completeEntry( string value)
        {
            StringBuilder sb = new StringBuilder();
            sb.Append(_parent._m_Program_Memory.getCurrentLine());
            sb.Append( value);
            _parent._m_Program_Memory.replaceLine(sb.ToString());
            _parent._m_Program_Memory.incrementCounter();
        }
    }
}
