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
    // Implements an unsigned 4-digit integer entry
    //
    public class Receiver_Address : Receiver
    {        
        private const string _AR_ButtonConversion = "####f########7410852#963#######ec";
        
        /// <summary>
        /// Inputs address
        /// </summary>
        public Receiver_Address(MK52_Host parent)
            : base( parent)
        {
            Moniker = "ADDRESS";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE( "ADR");
            lm.forcePaint();
            _text = new StringBuilder();
            _text.Append("    ");
        }

        public override byte tick(byte scancode)
        {
            char c = _convertButton(_AR_ButtonConversion, scancode);
            switch (c)
            {
                case 'e': // entry completed
                case 'f': // entry completed, action needed
                    completeEntry( toTrimmedString());
                    _parent.getFunctions().requestNextReceiver(_return_to);
                    return (c == 'e') ? (byte)0 : scancode;
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    _text.Remove(0, 1);
                    _text.Append(c);
                    if( _text[0] == ' ') break;
                    completeEntry(toTrimmedString());
                    _parent.getFunctions().requestNextReceiver(_return_to);
                    return 0;
                case 'c': // erase
                    _text.Remove(3, 1);
                    _text.Insert(0, ' ');
                    if (_text[3] != ' ') break;
                    completeEntry(toTrimmedString());
                    _parent.getFunctions().requestNextReceiver(_return_to);
                    return 0;
                default:
                    break;
            }
            updateDisplay(toString());
            return 0;
        }

        protected virtual void completeEntry( string value)
        {
            if (value.Length == 0)
            {
                _parent._m_Program_Memory.replaceLine_P("");
                return;
            }
            uint addr = Convert.ToUInt32(value);
            StringBuilder sb = new StringBuilder();
            sb.Append(_parent._m_Program_Memory.getCurrentLine());
            sb.Append(addr.ToString("0000"));
            _parent._m_Program_Memory.replaceLine(sb.ToString());
            _parent._m_Program_Memory.incrementCounter();
        }

        protected virtual void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            StringBuilder sb = new StringBuilder();
            sb.Append(_parent._m_Program_Memory.toString());
            sb.Append(toTrimmedString());
            lm.updateTerminalLine(10, sb.ToString());
            lm.forcePaint();
        }
    }
}
