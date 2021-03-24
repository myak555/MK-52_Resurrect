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
    public class Receiver_Text : Receiver
    {   
        private const string _RT_DigitConversion =  "### #<=>!,;:?7410852.963--+^E/*##";
        private const string _RT_LetterConversion = "#AIQ#BJRXCKSYDLTZEMU.FNV_GOW HP##";
        private const int _Off = 0;
        private const int _Text = 1;
        private const int _Number = 2;
        //private const int _K = 3;

        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_Text(MK52_Host parent)
            : base(parent)
        {
            Moniker = "TEXT";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            _mode = _Text;
            _text = new StringBuilder();
            _text.Append(_parent._m_Program_Memory.getCurrentLine());
            updateDisplay( toString());
        }

        public override byte tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions(); 
            switch( scancode)
            {
                case 0:
                    return 0;
                case 4:
                    _mode++;
                    if (_mode > _Number) _mode = _Text;
                    updateDisplay(toString());
                    return 0;
                case 31:
                    completeEntry(toString());
                    return _rpnf.requestNextReceiver(_return_to);
                case 32:
                    if( _text.Length > 0)
                        _text.Remove(_text.Length - 1, 1);
                    updateDisplay(toString());
                    return 0;
                case 33:
                    _rpnf.requestNextReceiver(_return_to);
                    return 33;
                default: 
                    break;
            }

            char c = (char)0;
            switch (_mode)
            {
                case _Text:
                    c = _convertButton(_RT_LetterConversion, scancode);
                    break;
                case _Number:
                    c = _convertButton(_RT_DigitConversion, scancode);
                    break;
                default:
                    break;
            }
            if (c == 0) return 0;
            if (_text.Length >= RPN_Functions.PROGRAM_LINE_LENGTH) return 0;
            _text.Append(c);
            updateDisplay(toString());
            return 0;
        }

        protected virtual void completeEntry(string value)
        {
            _parent._m_Program_Memory.replaceLine(value);
            _parent._m_Program_Memory.incrementCounter();
        }

        protected virtual void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            StringBuilder sb = new StringBuilder();
            sb.Append(_parent._m_Program_Memory.toCounterString());
            string tmp = toString();
            int ln = tmp.Length - LCD_Manager.SCREEN_COLS + 7;
            if (ln <= 0) sb.Append(tmp);
            else sb.Append(tmp.Substring(ln));
            lm.updateTerminalLine(10, sb.ToString());
            switch (_mode)
            {
                case _Text:
                    lm.updateStatusFMODE("TXT");
                    break;
                case _Number:
                    lm.updateStatusFMODE("NUM");
                    break;
                default:
                    lm.updateStatusFMODE("   ");
                    break;
            }
            lm.requestUpdate();
        }
    }
}
