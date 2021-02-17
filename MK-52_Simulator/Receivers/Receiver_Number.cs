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
        
        // fields used for entry editing
        public string Sign = " ";
        public string WholePart = "0";
        public string DecimalPart = "";
        public string ExpSign = "+";
        public string ExponentPart = "000";

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
            lm.Refresh();
            _text = new StringBuilder();
            _text.Append(' ');
            _mode = 1;
        }

        public override byte tick(byte scancode)
        {
            int ln = _text.Length;
            char c = _convertButton( _RN_ButtonConversion, scancode);
            switch( c)
            {
                case 'e': // entry completed
                case 'f': // entry completed, action needed
                    _mode = 0;
                    _parent._m_RPN_Stack.X.fromString(toTrimmedString()); 
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
                    if( ln == 2 && _text[1] == '0'){
                        _text[1] = c;
                        break;
                    }
                    if( _mode == 1 && ln>17) break;
                    if( _mode == 2 && ln>13) break;
                    if( _mode == 3)
                    {
                        _text[ln-3] = _text[ln-2]; 
                        _text[ln-2] = _text[ln-1]; 
                        _text[ln-1] = c; 
                        break;
                    }
                    _text.Append( c);
                    break;
                case '-':
                    if( _mode == 3)
                    {
                        _swapSign( ln - 4, '+');
                        break;
                    }
                    _swapSign( 0, ' ');
                    break;
                case '.':
                    if( _mode >= 2) break;
                    if (_mode == 1 && ln>12) break;
                    _mode = 2;
                    if( ln == 1)
                    {
                        _text.Append("0.");
                        break;
                    }
                    _text.Append('.');
                    break;
                case 'E':
                    if (_mode == 3)
                    {
                        _text.Remove(ln-5,5);
                        _mode = 2;
                        break;
                    }
                    if (_mode == 1 && ln > 12) break; // long integer
                    if (_mode == 1 && ln <= 1) // only sign present
                    {
                        _text.Append(_RN_StandardUnity);
                        _mode = 3;
                        break;
                    }
                    if (_mode == 1 && ln == 2 && _text[1] == '0') // integer zero
                    {
                        _text.Remove(1, 1);
                        _text.Append(_RN_StandardUnity);
                        _mode = 3;
                        break;
                    }
                    string tmp = toTrimmedString();
                    _uv.fromString(tmp);
                    if (_uv.isEmpty() || (_uv.isInt() && _uv.toInt() == 0))
                    {
                        _text = new StringBuilder();
                        _text.Append(' ');
                        _text.Append(_RN_StandardUnity);
                        _mode = 3;
                        break;
                    }
                    if (_mode == 1) // going from integer to exponent
                    {
                        _text.Append(_RN_StandardUnity.Substring(1));
                        _mode = 3;
                        break;
                    }

                    if ( UniversalValue._endsWith_P( tmp, ".")) // ends with decimal point
                    {
                        _text.Append(_RN_StandardUnity.Substring(2));
                        _mode = 3;
                        break;
                    }
                    _text.Append(_RN_StandardUnity.Substring(3));
                    _mode = 3;
                    break;
                case 'c': // erase
                    if( _mode == 3)
                    {
                        _text[ln-1] = _text[ln-2];
                        _text[ln-2] = _text[ln-3];
                        _text[ln-3] = '0';
                        break;
                    }
                    if( _mode == 2 && _text[ln-1] == '.')
                    {
                        _text.Remove( ln-1,1);
                        _mode = 1;
                        break;
                    }
                    if( ln>2)
                    {
                        _text.Remove(ln-1, 1);
                        break;
                    }
                    _mode = 0;
                    _parent._m_RPN_Stack.X.fromInt(0);
                    _parent.setReceiver(_return_to);
                    return 0;
                default:
                    break;
            }
            _parent.getLCD().updateCalcRegister(0, toString());
            _parent.getLCD().Refresh();
            return 0;
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

        void _swapSign( int pos, char plusChar)
        {
            _text[pos] = (_text[pos] == '-')? plusChar: '-';
        }

        ///// <summary>
        ///// Returns true if entry is on-going
        ///// </summary>
        //public override bool isActive
        //{
        //    get
        //    {
        //        return _mode != _Off;
        //    }
        //}

        ///// <summary>
        ///// Clears all substrings, resets the mode;
        ///// </summary>
        //public void Clear()
        //{
        //    Sign = " ";
        //    WholePart = "0";
        //    DecimalPart = "";
        //    ExpSign = "+";
        //    ExponentPart = "000";
        //    _mode = _Off;
        //}

        ///// <summary>
        ///// Called by the hardware button processing
        ///// </summary>
        ///// <param name="button">Button pressed</param>
        //public override string tick(MK52_Button button)
        //{
        //    switch (button.Moniker)
        //    {
        //        case "0":
        //        case "1":
        //        case "2":
        //        case "3":
        //        case "4":
        //        case "5":
        //        case "6":
        //        case "7":
        //        case "8":
        //        case "9":
        //            AddDigit(button.Moniker);
        //            return "Nothing";
        //        case ".":
        //            AddDecimal();
        //            return "Nothing";
        //        case "EE":
        //            AddExponent();
        //            return "Nothing";
        //        case "Cx":
        //            AddCx();
        //            return "Nothing";
        //        case "/-/":
        //            AddMinus();
        //            return "Nothing";
        //        default:
        //            return "Nothing";
        //    }
        //}

        ///// <summary>
        ///// Returns "NUM" if the receiver is active
        ///// </summary>
        //public override string DisplayName
        //{
        //    get
        //    {
        //        if ( isActive) return "NUM";
        //        return "   ";
        //    }
        //}

        ///// <summary>
        ///// Converts to human representation
        ///// </summary>
        ///// <returns></returns>
        //public override string ToString()
        //{
        //    StringBuilder sb = new StringBuilder("  ");
        //    //StringBuilder sb = new StringBuilder();
        //    sb.Append(Sign);
        //    sb.Append(WholePart);
        //    if (_mode == _Whole) return sb.ToString();
        //    sb.Append(".");
        //    sb.Append(DecimalPart);
        //    if (_mode == _Decimal) return sb.ToString();
        //    sb.Append("E");
        //    sb.Append(ExpSign);
        //    sb.Append(ExponentPart);
        //    return sb.ToString();
        //}

        ///// <summary>
        ///// Parses values
        ///// </summary>
        //public void FromValue(UniversalValue v)
        //{
        //    //Clear();
        //    //_mode = _Exponent;
        //    //if (v.isInt && v.asInt == 0)
        //    //{
        //    //    WholePart = "1";
        //    //    return;
        //    //}
        //    //string tmp = v.ToString();
        //    //if (tmp.StartsWith("-"))
        //    //{
        //    //    Sign = "-";
        //    //    tmp = tmp.Substring(1);
        //    //}
        //    //int i = tmp.IndexOf('.');
        //    //if (i < 0)
        //    //{
        //    //    WholePart = tmp;
        //    //    return;
        //    //}
        //    //WholePart = tmp.Substring(0, i);
        //    //tmp = tmp.Substring(i + 1);
        //    //if (tmp.Length <= 0) return;
        //    //i = tmp.IndexOf('E');
        //    //if (i < 0)
        //    //{
        //    //    DecimalPart = tmp;
        //    //    return;
        //    //}
        //    //DecimalPart = tmp.Substring(0, i);
        //    //tmp = tmp.Substring(i + 1);
        //    //ExpSign = tmp.Substring(0, 1);
        //    //ExponentPart = tmp.Substring(1);
        //}

        ///// <summary>
        ///// Sets value of RPN_Value from this
        ///// </summary>
        //public void ToValue(UniversalValue v)
        //{
        //    //if (_mode == _Off) return;
        //    //string tmp = Sign + WholePart;
        //    //tmp = tmp.Trim();
        //    //if (tmp.Length == 0) tmp = "0";
        //    //switch (_mode)
        //    //{
        //    //    case _Whole:
        //    //        v.asInt = Convert.ToInt64(tmp);
        //    //        break;
        //    //    case _Decimal:
        //    //        tmp += "." + DecimalPart;
        //    //        v.asReal = Convert.ToDouble(tmp);
        //    //        break;
        //    //    default:
        //    //        tmp += "." + DecimalPart + _limitExponent();
        //    //        v.asReal = Convert.ToDouble(tmp);
        //    //        break;
        //    //}
        //    //Clear();
        //}

        //#region Private Functions
        //private void AddDigit(string key)
        //{
        //    switch (_mode)
        //    {
        //        case _Off:
        //        case _Whole:
        //            _mode = _Whole;
        //            if (WholePart == "0") WholePart = key;
        //            else WholePart += key;
        //            return;
        //        case _Decimal:
        //            DecimalPart += key;
        //            return;
        //        default:
        //            ExponentPart += key;
        //            while (ExponentPart.Length > 3) ExponentPart = ExponentPart.Substring(1);
        //            return;
        //    }
        //}

        //private void AddDecimal()
        //{
        //    switch (_mode)
        //    {
        //        case _Off:
        //        case _Whole:
        //            _mode = _Decimal;
        //            if (WholePart == "") WholePart = "0";
        //            return;
        //        default:
        //            _mode = _Whole;
        //            DecimalPart = "";
        //            ExpSign = "+";
        //            ExponentPart = "000";
        //            return;
        //    }
        //}

        //private void AddExponent()
        //{
        //    switch (_mode)
        //    {
        //        case _Off:
        //        case _Whole:
        //        case _Decimal:
        //            _mode = _Exponent;
        //            if (WholePart == "") WholePart = "1";
        //            if (WholePart == "0") WholePart = "1";
        //            if (DecimalPart == "") DecimalPart = "0";
        //            return;
        //        default:
        //            _mode = _Decimal;
        //            if (DecimalPart == "0") DecimalPart = "";
        //            ExpSign = "+";
        //            ExponentPart = "000";
        //            return;
        //    }
        //}

        //private void AddCx()
        //{
        //    switch (_mode)
        //    {
        //        case _Off:
        //            return;
        //        case _Whole:
        //            WholePart = WholePart.Substring(0, WholePart.Length - 1);
        //            if (WholePart == "") WholePart = "0";
        //            return;
        //        case _Decimal:
        //            if (DecimalPart.Length <= 0)
        //            {
        //                _mode = _Whole;
        //                return;
        //            }
        //            DecimalPart = DecimalPart.Substring(0, DecimalPart.Length - 1);
        //            return;
        //        default:
        //            _mode = _Decimal;
        //            if (DecimalPart == "0") DecimalPart = "";
        //            ExpSign = "+";
        //            ExponentPart = "000";
        //            return;
        //    }
        //}

        //private void AddMinus()
        //{
        //    switch (_mode)
        //    {
        //        case _Off:
        //            return;
        //        case _Whole:
        //        case _Decimal:
        //            Sign = (Sign == " ") ? "-" : " ";
        //            return;
        //        default:
        //            ExpSign = (ExpSign == "+") ? "-" : "+";
        //            return;
        //    }
        //}

        ///// <summary>
        ///// Exponent cannot exceed 302
        ///// </summary>
        ///// <returns></returns>
        //private string _limitExponent()
        //{
        //    Int64 mant = Convert.ToInt64(WholePart);
        //    int limit = 302;
        //    while (mant > 1)
        //    {
        //        mant /= 10;
        //        limit--;
        //    }
        //    int tmp = Convert.ToInt32( ExpSign + ExponentPart);
        //    if (tmp < -limit) tmp = -limit;
        //    if (tmp > limit) tmp = limit;
        //    return "E" + tmp.ToString();
        //}
        //#endregion
    }
}
