using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    //
    // Implements the state engine
    //
    public class RPN_XEntry
    {        
        // editing mode - user edits register x
        public const int Mode_Off = 0;
        public const int Mode_Whole = 1;
        public const int Mode_Decimal = 2;
        public const int Mode_Exponent = 3;
        public int Mode = Mode_Off;
        
        // fields used for entry editing
        public string Sign = " ";
        public string WholePart = "0";
        public string DecimalPart = "";
        public string ExpSign = "+";
        public string Exponent = "000";

        private RPN_Calculator _parent = null;  

        // controls an extra push by Enter button / command
        public bool pushOnEntryRequired = true;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="parent"></param>
        public RPN_XEntry(RPN_Calculator parent)
        {
            _parent = parent;
        }

        /// <summary>
        /// Clears all substrings
        /// </summary>
        public void Clear()
        {
            Sign = " ";
            WholePart = "0";
            DecimalPart = "";
            ExpSign = "+";
            Exponent = "000";
        }

        /// <summary>
        /// Called by the hardware button processing
        /// </summary>
        /// <param name="key"></param>
        public void NewEntry( string key)
        {
            if (pushOnEntryRequired)
                _parent.Memory.PushStack(1);
            pushOnEntryRequired = true;
            Clear();
            if ( key != ".")
            {
                WholePart = key;
                Mode = Mode_Whole;
                return;
            }
            WholePart = "0";
            Mode = Mode_Decimal;
        }

        /// <summary>
        /// Converts to human representation
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            StringBuilder sb = new StringBuilder("  ");
            sb.Append(Sign);
            sb.Append(WholePart);
            if (Mode == Mode_Whole) return sb.ToString();
            sb.Append(".");
            sb.Append(DecimalPart);
            if (Mode == Mode_Decimal) return sb.ToString();
            sb.Append("E");
            sb.Append(ExpSign);
            sb.Append(Exponent);
            return sb.ToString();
        }

        /// <summary>
        /// Parses values into the calculator editor
        /// </summary>
        public void FromValue(RPN_Value v)
        {
            Mode = Mode_Exponent;
            Clear();
            if (v.isInt && v.asInt == 0)
            {
                WholePart = "1";
                return;
            }
            string tmp = v.ToString();
            if (tmp.StartsWith("-"))
            {
                Sign = "-";
                tmp = tmp.Substring(1);
            }
            int i = tmp.IndexOf('.');
            if (i < 0)
            {
                WholePart = tmp;
                return;
            }
            WholePart = tmp.Substring(0, i);
            tmp = tmp.Substring(i + 1);
            if (tmp.Length <= 0) return;
            i = tmp.IndexOf('E');
            if (i < 0)
            {
                DecimalPart = tmp;
                return;
            }
            DecimalPart = tmp.Substring(0, i);
            tmp = tmp.Substring(i + 1);
            ExpSign = tmp.Substring(0, 1);
            Exponent = tmp.Substring(1);
        }

        /// <summary>
        /// Sets value of RPN_Value from this
        /// </summary>
        public void ToValue(RPN_Value v)
        {
            string tmp = Sign + WholePart;
            tmp = tmp.Trim();
            if (tmp.Length == 0) tmp = "0";
            switch (Mode)
            {
                case Mode_Whole:
                    v.asInt = Convert.ToInt64(tmp);
                    return;
                case Mode_Decimal:
                    tmp += "." + DecimalPart;
                    v.asReal = Convert.ToDouble(tmp);
                    return;
                default:
                    tmp += "." + DecimalPart + _limitExponent();
                    v.asReal = Convert.ToDouble(tmp);
                    return;
            }
        }


        /// <summary>
        /// Converts value and loads into the stack
        /// </summary>
        /// <returns>value just entered</returns>
        public RPN_Value LoadEditValue()
        {
            if (Mode != Mode_Off)
            {
                ToValue(_parent.Memory.StackValues[0]);
                Mode = Mode_Off;
            }
            return _parent.Memory.StackValues[0];
        }

        /// <summary>
        /// Exponent cannot exceed 302
        /// </summary>
        /// <returns></returns>
        private string _limitExponent()
        {
            Int64 mant = Convert.ToInt64(WholePart);
            int limit = 302;
            while (mant > 1)
            {
                mant /= 10;
                limit--;
            }
            int tmp = Convert.ToInt32( ExpSign + Exponent);
            if (tmp < -limit) tmp = -limit;
            if (tmp > limit) tmp = limit;
            return "E" + tmp.ToString();
        }
    }
}
