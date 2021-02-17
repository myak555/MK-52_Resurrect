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
    // Implements a numeric data entry editor
    //
    public class Receiver_Number : Receiver
    {        
        private const string _RN_ButtonConversion = "#ffffffffffff7410852.963-fffEffec";
        private const string _RN_StandardUnity = "1.0E+000";

        private const int _Off = 0;
        private const int _Whole = 1;
        private const int _Decimal = 2;
        private const int _Exponent = 3;
        
        /// <summary>
        /// Constructor
        /// </summary>
        public Receiver_Number(MK52_Host parent):
            base( parent)
        {
            Moniker = "NUMBER";
        }

        public override void activate(string prevReceiver)
        {
            base.activate(prevReceiver);
            LCD_Manager lm = _parent.getLCD();
            lm.updateStatusFMODE( "NUM");
            lm.forcePaint();
            _text = new StringBuilder();
            _text.Append(' ');
            _mode = _Whole;
        }

        public override byte tick(byte scancode)
        {
            int ln = _text.Length;
            char c = _convertButton( _RN_ButtonConversion, scancode);
            switch( c)
            {
                case 'e': // entry completed
                case 'f': // entry completed, action needed
                    _mode = _Off;
                    completeEntry( toTrimmedString());
                    _parent.setReceiver( _return_to);
                    return (c=='e')? (byte)0: scancode;
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
                    processDigit(ln, c);
                    break;
                case '-':
                    if( _mode == _Exponent)
                    {
                        _swapSign( ln - 4, '+');
                        break;
                    }
                    _swapSign( 0, ' ');
                    break;
                case '.':
                    if( _mode >= _Decimal) break;
                    if (_mode == _Whole && ln>12) break;
                    _mode = _Decimal;
                    if( ln == 1)
                    {
                        _text.Append("0.");
                        break;
                    }
                    _text.Append('.');
                    break;
                case 'E':
                    processExponent(ln);
                    break;
                case 'c': // erase
                    if( processCx(ln)) return 0;
                    break;
                default:
                    break;
            }
            updateDisplay(toString());
            return 0;
        }

        protected virtual void completeEntry( string value)
        {
            _parent._m_RPN_Stack.X.fromString(value); 
        }

        protected virtual void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD(); 
            lm.updateCalcRegister(0, toString());
            lm.forcePaint();
        }

        public string toString()
        {
            return _text.ToString();
        }

        public override string ToString()
        {
            return _text.ToString();
        }

        public string toTrimmedString()
        {
            return _text.ToString().TrimStart();
        }

        private void processDigit(int ln, char c)
        {
            if (ln == 2 && _text[1] == '0')
            {
                _text[1] = c;
                return;
            }
            if (_mode == _Whole && ln > 17) return;
            if (_mode == _Decimal && ln > 13) return;
            if (_mode == _Exponent)
            {
                _text[ln - 3] = _text[ln - 2];
                _text[ln - 2] = _text[ln - 1];
                _text[ln - 1] = c;
                return;
            }
            _text.Append(c);
            return;
        }

        private void processExponent(int ln)
        {
            if (_mode == _Exponent)
            {
                _text.Remove(ln - 5, 5);
                _mode = _Decimal;
                return;
            }
            if (_mode == _Whole && ln > 12) return; // long integer
            if (_mode == _Whole && ln <= 1) // only sign present
            {
                _text.Append(_RN_StandardUnity);
                _mode = _Exponent;
                return;
            }
            if (_mode == _Whole && ln == 2 && _text[1] == '0') // integer zero
            {
                _text.Remove(1, 1);
                _text.Append(_RN_StandardUnity);
                _mode = _Exponent;
                return;
            }
            string tmp = toTrimmedString();
            _uv.fromString(tmp);
            if (_uv.isEmpty() || (_uv.isInt() && _uv.toInt() == 0))
            {
                _text = new StringBuilder();
                _text.Append(' ');
                _text.Append(_RN_StandardUnity);
                _mode = _Exponent;
                return;
            }
            if (_mode == _Whole) // going from integer to exponent
            {
                _text.Append(_RN_StandardUnity.Substring(1));
                _mode = _Exponent;
                return;
            }

            if (UniversalValue._endsWith_P(tmp, ".")) // ends with decimal point
            {
                _text.Append(_RN_StandardUnity.Substring(2));
                _mode = _Exponent;
                return;
            }

            _text.Append(_RN_StandardUnity.Substring(3));
            _mode = _Exponent;
        }

        private bool processCx(int ln)
        {
            if (_mode == _Exponent)
            {
                _text[ln - 1] = _text[ln - 2];
                _text[ln - 2] = _text[ln - 3];
                _text[ln - 3] = '0';
                return false;
            }
            if (_mode == _Decimal && _text[ln - 1] == '.')
            {
                _text.Remove(ln - 1, 1);
                _mode = _Whole;
                return false;
            }
            if (ln > 2)
            {
                _text.Remove(ln - 1, 1);
                return false;
            }
            _mode = _Off;
            completeEntry("0");
            _parent.setReceiver(_return_to);
            return true;
        }

        private void _swapSign( int pos, char plusChar)
        {
            _text[pos] = (_text[pos] == '-')? plusChar: '-';
        }
    }
}
