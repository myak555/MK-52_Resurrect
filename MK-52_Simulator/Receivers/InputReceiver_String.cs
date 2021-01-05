using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator.Receivers
{
    //
    // Implements a text data entry editor
    //
    public class InputReceiver_String : RPN_InputReceiver
    {        
        private const int _Off = 0;
        private const int _Text = 1;
        private const int _Number = 2;
        private const int _K = 3;
        private int _mode = _Off;
        
        // fields used for entry editing
        public string EntryText = "";

        /// <summary>
        /// Constructor
        /// </summary>
        public InputReceiver_String(RPN_Calculator parent)
            : base(parent)
        {
            Clear();
        }

        /// <summary>
        /// Returns true if entry is on-going
        /// </summary>
        public override bool isActive
        {
            get
            {
                return _mode != _Off;
            }
        }

        /// <summary>
        /// Clears all substrings, resets the mode;
        /// </summary>
        public void Clear()
        {
            EntryText = "";
            _mode = _Off;
        }

        /// <summary>
        /// Called by the hardware button processing
        /// </summary>
        /// <param name="key">Button pressed</param>
        public override void onButton(RPN_Button button)
        {
            switch (_mode)
            {
                case _Off:
                    _mode = _Text;
                    AddLetter( button);
                    return;
                case _Text:
                    AddLetter(button);
                    return;
                case _Number:
                    AddDigit(button);
                    return;
                default:
                    return;
            }
        }

        private void AddDigit(RPN_Button button)
        {
            //EntryText += key;
            //switch (_mode)
            //{
            //    case _Off:
            //    case _Whole:
            //        _mode = _Whole;
            //        if (WholePart == "0") WholePart = key;
            //        else WholePart += key;
            //        return;
            //    case _Number:
            //        DecimalPart += key;
            //        return;
            //    default:
            //        ExponentPart += key;
            //        while (ExponentPart.Length > 3) ExponentPart = ExponentPart.Substring(1); 
            //        return;
            //}
        }

        private void AddLetter( RPN_Button button)
        {
            //switch (button.Moniker)
            //{
            //    case "Func F":
            //    case "Func K":
            //    case "Func A":
            //        return;
            //    case "Mode":
            //        _mode = _Number;
            //        return;

            //    case _Whole:
            //        _mode = _Whole;
            //        if (WholePart == "0") WholePart = key;
            //        else WholePart += key;
            //        return;
            //    case _Number:
            //        DecimalPart += key;
            //        return;
            //    default:
            //        ExponentPart += key;
            //        while (ExponentPart.Length > 3) ExponentPart = ExponentPart.Substring(1);
            //        return;
            //}
        }

        /// <summary>
        /// Converts to human representation
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return EntryText;
        }
    }
}
