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
        protected RPN_Stack _stackInput = null;

        public const uint _Off = 0;
        public const uint _Whole = 1;
        public const uint _Decimal = 2;
        public const uint _Exponent = 3;
        
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
            _stackInput = _parent._m_RPN_Stack;
            _stackInput._DataEntry = new StringBuilder();
            _stackInput._DataEntry.Append(' ');
            _mode = _Whole;
        }

        public override byte tick(byte scancode)
        {
            int ln = _stackInput._DataEntry.Length;
            char c = _convertButton( _RN_ButtonConversion, scancode);
            switch( c)
            {
                case 'e': // entry completed
                case 'f': // entry completed, action needed
                    _mode = _Off;
                    completeEntry( toTrimmedString());
                    _parent.getFunctions().requestNextReceiver(_return_to);
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
                        _stackInput._DataEntry.Append("0.");
                        break;
                    }
                    _stackInput._DataEntry.Append('.');
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
            _stackInput.X.fromString(value); 
        }

        protected virtual void updateDisplay(string value)
        {
            LCD_Manager lm = _parent.getLCD(); 
            lm.updateCalcRegister(0, toString());
            lm.forcePaint();
        }

        public override string toString()
        {
            return _stackInput._DataEntry.ToString();
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Receiver [");
            sb.Append(Moniker);
            sb.Append("]: ");
            sb.Append(_stackInput._DataEntry.ToString());
            return sb.ToString();
        }

        public override string toTrimmedString()
        {
            return _stackInput._DataEntry.ToString().TrimStart();
        }

        private void processDigit(int ln, char c)
        {
            if (ln == 2 && _stackInput._DataEntry[1] == '0')
            {
                _stackInput._DataEntry[1] = c;
                return;
            }
            if (_mode == _Whole && ln > 17) return;
            if (_mode == _Decimal && ln > 13) return;
            if (_mode == _Exponent)
            {
                _stackInput._DataEntry[ln - 3] = _stackInput._DataEntry[ln - 2];
                _stackInput._DataEntry[ln - 2] = _stackInput._DataEntry[ln - 1];
                _stackInput._DataEntry[ln - 1] = c;
                return;
            }
            _stackInput._DataEntry.Append(c);
            return;
        }

        private void processExponent(int ln)
        {
            if (_mode == _Exponent)
            {
                _stackInput._DataEntry.Remove(ln - 5, 5);
                _mode = _Decimal;
                return;
            }
            if (_mode == _Whole && ln > 12) return; // long integer
            if (_mode == _Whole && ln <= 1) // only sign present
            {
                _stackInput._DataEntry.Append(_RN_StandardUnity);
                _mode = _Exponent;
                return;
            }
            if (_mode == _Whole && ln == 2 && _stackInput._DataEntry[1] == '0') // integer zero
            {
                _stackInput._DataEntry.Remove(1, 1);
                _stackInput._DataEntry.Append(_RN_StandardUnity);
                _mode = _Exponent;
                return;
            }
            string tmp = toTrimmedString();
            _uv.fromString(tmp);
            if (_uv.isEmpty() || (_uv.isInt() && _uv.toInt() == 0))
            {
                _stackInput._DataEntry = new StringBuilder();
                _stackInput._DataEntry.Append(' ');
                _stackInput._DataEntry.Append(_RN_StandardUnity);
                _mode = _Exponent;
                return;
            }
            if (_mode == _Whole) // going from integer to exponent
            {
                _stackInput._DataEntry.Append(_RN_StandardUnity.Substring(1));
                _mode = _Exponent;
                return;
            }

            if (UniversalValue._endsWith_P(tmp, ".")) // ends with decimal point
            {
                _stackInput._DataEntry.Append(_RN_StandardUnity.Substring(2));
                _mode = _Exponent;
                return;
            }

            _stackInput._DataEntry.Append(_RN_StandardUnity.Substring(3));
            _mode = _Exponent;
        }

        private bool processCx(int ln)
        {
            if (_mode == _Exponent)
            {
                _stackInput._DataEntry[ln - 1] = _stackInput._DataEntry[ln - 2];
                _stackInput._DataEntry[ln - 2] = _stackInput._DataEntry[ln - 3];
                _stackInput._DataEntry[ln - 3] = '0';
                return false;
            }
            if (_mode == _Decimal && _stackInput._DataEntry[ln - 1] == '.')
            {
                _stackInput._DataEntry.Remove(ln - 1, 1);
                _mode = _Whole;
                return false;
            }
            if (ln > 2)
            {
                _stackInput._DataEntry.Remove(ln - 1, 1);
                return false;
            }
            _mode = _Off;
            completeEntry("0");
            _parent.getFunctions().requestNextReceiver(_return_to);
            return true;
        }

        private void _swapSign( int pos, char plusChar)
        {
            _stackInput._DataEntry[pos] = (_stackInput._DataEntry[pos] == '-')? plusChar: '-';
        }
    }
}
