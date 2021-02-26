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
    public class Receiver_FILE_Name : Receiver
    {
        private const string _RT_DigitConversion = "### ####!,###7410852.963_-###/###";
        private const string _RT_LetterConversion = "#AIQ#BJRXCKSYDLTZEMU.FNV_GOW HP##";
        protected string _Question = "File name?";
        protected string _Confirmation = "Overwrite? (\u0018)";
        protected string _Ext = ".MK52";
        private const int _Off = 0;
        private const int _Text = 1;
        private const int _Number = 2;
        private const int _Overwrite = 3;

        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_FILE_Name(MK52_Host parent)
            : base(parent)
        {
            Moniker = "File_Name";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            _text = new StringBuilder();
            _mode = _Text;
            updateDisplay(toString());
        }

        public override byte tick(byte scancode)
        {
            if (_mode < _Overwrite) return _mode1_Tick(scancode);
            return _mode2_Tick(scancode);
        }

        protected virtual byte _mode1_Tick(byte scancode)
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
                    return 0;
                case 32:
                    if (_text.Length <= 0)
                    {
                        _parent.getFunctions().requestNextReceiver(_return_to);
                        return 0;
                    }
                    _text.Remove(_text.Length - 1, 1);
                    updateDisplay(toString());
                    return 0;
                case 33:
                    _parent.getFunctions().requestNextReceiver(_return_to);
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

        protected virtual byte _mode2_Tick(byte scancode)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            switch (scancode)
            {
                case 0:
                    return 0;
                case 31:
                    completeEntry(toString());
                    _rpnf.requestNextReceiver(_return_to);
                    return 0;
                case 32:
                    _rpnf.requestNextReceiver(_return_to);
                    return 0;
                case 33:
                    _rpnf.requestNextReceiver(_return_to);
                    return 33;
                default:
                    _mode = _Text;
                    break;
            }
            return scancode;
        }

        protected virtual void completeEntry(string value)
        {
            RPN_Functions _rpnf = _parent.getFunctions();
            string tmpName = _rpnf.formFileName(value);
            if (!UniversalValue._endsWith_P(value, _Ext)) tmpName += _Ext;
            if( _rpnf.fileExists(tmpName))
            {
                _mode = _Overwrite;
                updateDisplay(toString());
                return;
            }
            _rpnf.saveProgramFile( tmpName);
            _parent.getFunctions().requestNextReceiver(_return_to);
            return;
        }

        protected virtual void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD();
            int ln = value.Length - LCD_Manager.SCREEN_COLS + 1;
            lm.updateTerminalLine(LCD_Manager.SCREEN_ROWS - 2,
                (ln <= 0)? value: value.Substring(ln));
            switch (_mode)
            {
                case _Text:
                    lm.updateStatusFMODE("TXT");
                    lm.updateTerminalLine(LCD_Manager.SCREEN_ROWS - 3, _Question);
                    break;
                case _Number:
                    lm.updateStatusFMODE("NUM");
                    lm.updateTerminalLine(LCD_Manager.SCREEN_ROWS - 3, _Question);
                    break;
                default:
                    lm.updateStatusFMODE("   ");
                    lm.updateTerminalLine(LCD_Manager.SCREEN_ROWS - 3, _Confirmation);
                    break;
            }
            lm.forcePaint();
        }
    }
}
