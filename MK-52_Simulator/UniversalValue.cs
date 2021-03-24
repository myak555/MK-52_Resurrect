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
    public class UniversalValue
    {
        private const string _standard_DoubleFormat = "0.0"; //"%f";
        private const string _standard_FullPrecision = "0.00000000000"; //"%13.11f";  
        //private const string _standard_FullPrecision = "0.0000000"; //"%9.7f";  
        private const double _standard_ConvertLow = 0.999999999999;
        private const double _standard_ConvertHigh = 9.99999999999;
        private const string _standard_ExponentFormat = "+000;-000"; //"%+04d";  
        private const string _standard_Error = "Error";  
        private const string _standard_MinusInfinity = "-Inf";  
        private const string _standard_PlusInfinity = "+Inf";  
        private const string _standard_Decimals = "0123456789";
        private const string _standard_NumberComponents = "0123456789.+-eE";

        public const Int64 HUGE_POSITIVE_INTEGER = 9000000000000000000L;
        public const Int64 HUGE_NEGATIVE_INTEGER = -9000000000000000000L;
        public const double HUGE_POSITIVE_AS_REAL = 9e18;
        public const double HUGE_NEGATIVE_AS_REAL = -9e18;
        public const double __PI = 3.141592653589793;
        public const double __PI4 = 0.7853981633974483;
        public const double __EE = 2.718281828459045;
        public const double __ROUNDING_ACCURACY = 1e11;
        public const byte VALUE_TYPE_EMPTY = 0;
        public const byte VALUE_TYPE_INTEGER = 1;
        public const byte VALUE_TYPE_DOUBLE = 2;

        private byte _m_Type;
        private double _m_dVal;
        private Int64 _m_iVal;

        /// <summary>
        /// Deliberately simulates C++ for ESP32 porting
        /// Methods are "C++ish"
        /// </summary>
        public UniversalValue()
        {
            fromEmpty();
        }

        public byte getType()
        {
            return _m_Type;
        }
        
        public bool isEmpty()
        {
            return _m_Type == VALUE_TYPE_EMPTY;
        }

        public bool isInt()
        {
            return _m_Type == VALUE_TYPE_INTEGER;
        }

        public bool isReal()
        {
            return _m_Type == VALUE_TYPE_DOUBLE;
        }

        public void fromEmpty()
        {
            _m_Type = VALUE_TYPE_EMPTY;
            _m_dVal = 0.0;
            _m_iVal = 0L;
        }

        public void fromInt(Int64 value)
        {
            _m_Type = VALUE_TYPE_INTEGER;
            _m_dVal = 0.0;
            _m_iVal = value;
        }

        public void fromReal(double value)
        {
            _m_Type = VALUE_TYPE_DOUBLE;
            _m_dVal = value;
            _m_iVal = 0L;
            _checkRounding();
        }

        public byte fromLocation( UniversalValue value)
        {
            _m_Type = value._m_Type;
            _m_dVal = value._m_dVal;
            _m_iVal = value._m_iVal;
            return _m_Type;
        }                

        public byte fromString( string text)
        {
            text = text.TrimStart();
            if( text.StartsWith( "Error"))
            {
                fromReal( double.NaN);
                return getType();
            }
            if (text.StartsWith("+Inf"))
            {
                fromReal(double.PositiveInfinity);
                return getType();
            }
            if (text.StartsWith("-Inf"))
            {
                fromReal(double.NegativeInfinity);
                return getType();
            }
            string ptr = text;
            bool positive = true;
            if( ptr.StartsWith( "+")) ptr = ptr.Substring(1);
            if( ptr.StartsWith( "-"))
            {
                ptr = ptr.Substring(1);
                positive = false;
            }
            int ln = ptr.Length;
            if( ln <= 0)
            {
                fromEmpty();
                return getType();
            }
            int indexE = ptr.IndexOf( 'E');
            if (indexE < 0) indexE = ptr.IndexOf('e');
            int indexDecimal = ptr.IndexOf('.');
            if( indexE < 0 && indexDecimal < 0) // no decimal or e - whole number
            { 
                fromInt( _recoverInt64( text));        
                return getType();
            }
            double result = 0.0;
            Int64 exponent = 0;
            if( indexE < 0 && indexDecimal >= 0) // has decimal, but no e
            {
                result = (double)_recoverInt64( ptr);
                result += _recoverDecimal( ptr.Substring( indexDecimal+1));
                fromReal( positive? result: -result);        
                return getType();
            }

            // has e
            result = (double)_recoverInt64( ptr);
            if( indexDecimal >= 0)
                result += _recoverDecimal(ptr.Substring( indexDecimal+1));
            exponent = _recoverInt64( ptr.Substring( indexE+1));
            if( exponent < -300)
            {
                fromInt( 0);        
                return getType();
            }
            if( exponent > 300) // infinity
            { 
                fromReal( positive? double.PositiveInfinity: double.NegativeInfinity);        
                return getType();
            }
            int ex2 = (int)exponent;
            while( ex2 > 0)
            {
                result *= 10.0;
                ex2--;
            }
            while( ex2 < 0)
            {
                result *= 0.1;
                ex2++;
            }
            fromReal( positive? result: -result);        
            return getType();
        }

        public Int64 toInt()
        {
            if(isEmpty()) return 0L;
            if(isInt()) return _m_iVal;
            if( _m_dVal > HUGE_POSITIVE_AS_REAL) return HUGE_POSITIVE_INTEGER; 
            if( _m_dVal < HUGE_NEGATIVE_AS_REAL) return HUGE_NEGATIVE_INTEGER;
            return (Int64)_m_dVal; 
        }

        public double toReal(){
            if(isEmpty()) return 0.0;
            if(isReal()) return _m_dVal;
            return (double)_m_iVal; 
        }
        
        public UniversalValue toBytes()
        {
            UniversalValue uv = new UniversalValue();
            uv.fromLocation( this);
            return uv;
        }

        public byte toLocation( UniversalValue uv)
        {
            uv._m_Type = this._m_Type;
            uv._m_dVal = this._m_dVal;
            uv._m_iVal = this._m_iVal;
            return uv._m_Type;
        }

        public override string ToString()
        {
            return this.toString();
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public string toString()
        {
            if(isEmpty()) return "";
            if(isInt()) return _composeInt64( toInt());
            return _composeDouble( toReal());
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public Int64 _asIntPtr()
        {
            return _m_iVal;
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public double _asRealPtr()
        {
            return _m_dVal;
        }
            
        public void _checkRounding()
        {
            _checkRounding(__ROUNDING_ACCURACY);
        }

        public void _checkRounding( double accuracy)
        {
            if( !isReal()) return;
            double value = _m_dVal;
            if( double.IsNaN(value)) return;
            if( double.IsInfinity(value)) return;
            bool positive = true;
            if( value < 0.0)
            {
                positive = false;
                value = -value;
            }
            if( value < 1.0e-300) // true zero;
            { 
                fromInt( 0);
                return;
            }
            if (value >= HUGE_POSITIVE_AS_REAL) return; // should not convert
            double rValue = Math.Round(value);
            if (value > accuracy && Math.Abs(value - rValue) < accuracy / HUGE_POSITIVE_AS_REAL)
            {
                fromInt((Int64)rValue);
                return; // This must be an int
            }

            if( value >= accuracy) return; // should not convert
            if (value < _standard_ConvertLow) return; // whole part < 1. 
            if( value < 1.00000000001)
            {
                fromInt( positive? 1: -1);
                return;
            }

            double vLimit = accuracy;
            double cutoff = 0.3;
            while( value < vLimit)
            {
                vLimit *= 0.1;
                cutoff *= 0.1;
            }
            double fl = Math.Floor(value);
            double frac = value - fl;
            if( cutoff < frac && frac < 1.0-cutoff) return; // meaningful decimal present
            if( frac > 0.5) fl += 1.0;
            
            fromInt( positive? (Int64)fl: -(Int64)fl);
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _startsWith(string text, string keyword)
        {
            return text.StartsWith( keyword);
        }
      
        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _startsWith_P(string text, string keyword)
        {
            return text.StartsWith( keyword);
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _endsWith_P(string text, string keyword)
        {
            return text.EndsWith( keyword);
        }
        
        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _identicalTo_P(string text, string keyword)
        {
            return text.CompareTo( keyword) == 0;
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _inString_P(char c, string keyword)
        {
            return keyword.IndexOf(c) >= 0;
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _isDigit(char c)
        {
            return _inString_P(c, _standard_Decimals);
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _looksLikeANumber(string text)
        {
            if (text.Length == 0) return false;
            if( text == "Error") return true;
            if( text == "+Inf") return true;
            if( text == "-Inf") return true;
            for( int i=0; i<text.Length; i++)
            {
                if( !_inString_P(text[i], _standard_NumberComponents)) return false;
            }
            return true;
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _isProgramAddress(string text)
        {
            if( text[0] != 'P') return false;
            return _isAddress(text.Substring(1));
        }
                
        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _isMemoryAddress(string text)
        {
            if (text[0] != 'M') return false;
            return _isAddress(text.Substring(1));
        }
       
        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static byte _isRegisterAddress(string text)
        {
            if( text[0] != 'R') return 20;
            if( !_isDigit(text[1])) return 20;
            byte val = (byte)_standard_Decimals.IndexOf(text[1]);
            if( !_isDigit(text[2])) return 20;
            val *= 10;
            val += (byte)_standard_Decimals.IndexOf(text[2]);
            if( text[3] != '=') return 20;
            return val;
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _isReturnStackAddress(string text)
        {
            if (text[0] != 'S') return false;
            return _isAddress(text.Substring(1));
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _isAddress(string text){
            for( int i=0; i<4; i++)
            {
                if( !_isDigit(text[i])) return false;
            }
            return text[4] == ':' && text[5] == ' ';
        }

        /// <summary>
        /// Breaks the program line into tokens
        /// </summary>
        /// <param name="text"></param>
        /// <returns>address string and content </returns>
        public static string[] _selectAddress(string text)
        {
            string[] tmp = new string[2]; 
            text = text.Substring(1);
            tmp[0] = "";
            tmp[1] = "";
            for( int i=0; i<5; i++)
            {
                if( _isDigit(text[i])) continue;
                if( text[i] == ':')
                {
                    tmp[0] = text.Substring(0, i);
                    tmp[1] = text.Substring(i+2);
                    break;
                }
            }
            return tmp;
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        public static bool _containsChar(string text, char c)
        {
            return text.IndexOf( c) >= 0;
        }

        public static string _composeDouble(double value)
        { 
            if( double.IsNaN(value)) return _standard_Error;
            if( double.IsNegativeInfinity(value)) return _standard_MinusInfinity;
            if( double.IsPositiveInfinity(value)) return _standard_PlusInfinity;
            bool negative = false;
            if( value < 0.0){
                negative = true;
                value = -value;
            } 
            if( 0.1 <= value && value < 1e12)
                return _composeFloat(negative? -value: value);

            int exponent = 0;
            while (value < _standard_ConvertLow)
            {
                exponent--;
                value *= 10.0;
            }
            while (value >= _standard_ConvertHigh)
            {
                exponent++;
                value *= 0.1;
            }
            StringBuilder text = new StringBuilder();
            text.Append(negative ? '-' : ' '); 
            text.Append(value.ToString(_standard_FullPrecision));
            text.Append('E');
            text.Append(exponent.ToString(_standard_ExponentFormat));
            return text.ToString();
        }

        private static string _composeFloat(double value)
        {
            if (value == 0.0) return "0";
            StringBuilder ptr = new StringBuilder();
            if( value < 0.0)
            {
                ptr.Append('-');
                value = -value;
            }

            // print whole part
            double fl = Math.Floor( value);
            string tmp = _composeInt64((Int64)fl);

            // how many digits should we have?
            int ln = tmp.Length;
            int decimals = 12 - ln;
            if( decimals <= 0)
            {
                fl = Math.Round( value);
                ptr.Append( _composeInt64((Int64)fl));
                ptr.Append( ".0");
                return ptr.ToString();
            }

            // print with fractional part
            if (fl == 0) ptr.Append('0'); // for case < 1.0
            for( int i=0; i<decimals; i++) value *= 10.0;
            tmp = _composeInt64((Int64)Math.Round(value));
            ptr.Append(tmp.Substring(0, tmp.Length - decimals));
            ptr.Append('.');
            ln = ptr.Length + 1;
            ptr.Append(tmp.Substring(tmp.Length - decimals));
            tmp = ptr.ToString();

            // remove meaningless zeros from the end
            while( tmp.Length > ln && tmp.EndsWith("0"))
                tmp = tmp.Substring(0, tmp.Length-1);
            return tmp;
        }

        public static string _composeInt64(Int64 value)
        { 
            if( value > HUGE_POSITIVE_INTEGER) return _standard_MinusInfinity;
            if( value < HUGE_NEGATIVE_INTEGER) return _standard_PlusInfinity;

            // my own version of lltoa
            // return lltoa( value, text, 10);
            StringBuilder ptr = new StringBuilder();
            if( value == 0L)
            { 
                ptr.Append('0');
                return ptr.ToString();
            }
            if( value < 0)
            {
                ptr.Append('-');
                value = -value;
            }
            Int64 mult = 1000000000000000000L;
            while( mult > 0 && (value / mult) == 0) mult /= 10;
            while( mult > 0)
            {
                int tt = (int)(value / mult);
                ptr.Append(_standard_Decimals[tt]);
                value %= mult;
                mult /= 10;
            }
            return ptr.ToString();
        }

        private static double _recoverDecimal(string ptr)
        {
            double tmp = 0.0;
            double frac = 0.1;
            for( int i=0; i<ptr.Length; i++)
            {
                if( !_isDigit( ptr[i])) return tmp;
                tmp += frac * (_standard_Decimals.IndexOf(ptr[i]));
                frac *= 0.1;
                if( frac < 1e-12) return tmp;
            }
            return tmp;
        }

        private static Int64 _recoverInt64(string ptr)
        {
            bool positive = true;
            int index = 0;
            if( ptr[index] == '-')
            {
                index++;
                positive = false;
            }
            if( ptr[index] == '+') index++;
            Int64 tmp = 0;
            while( index < ptr.Length)
            {
                if( !_isDigit( ptr[index]))
                    return positive? tmp: -tmp;
                tmp *= 10L;
                tmp += _standard_Decimals.IndexOf(ptr[index]);
                if( tmp > HUGE_POSITIVE_INTEGER)
                    return positive? HUGE_POSITIVE_INTEGER: HUGE_NEGATIVE_INTEGER;
                index++;
            }
            return positive? tmp: -tmp;
        }
    }
}
