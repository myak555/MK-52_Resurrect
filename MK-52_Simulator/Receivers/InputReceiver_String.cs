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
    public class InputReceiver_String : Receiver
    {        
        private const int _Off = 0;
        private const int _Text = 1;
        private const int _Number = 2;
        private const int _K = 3;
        
        // fields used for entry editing
        public string EntryText = "";

        /// <summary>
        /// Constructor
        /// </summary>
        public InputReceiver_String(MK52_Host parent)
            : base(parent)
        {
            //Clear();
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

        //public void ActivateEntry()
        //{
        //    EntryText = "";
        //    _mode = _Text;
        //}

        ///// <summary>
        ///// Clears all substrings, resets the mode;
        ///// </summary>
        //public void Clear()
        //{
        //    EntryText = "";
        //    _mode = _Off;
        //}

        ///// <summary>
        ///// Called by the hardware button processing
        ///// </summary>
        ///// <param name="key">Button pressed</param>
        //public override string tick(MK52_Button button)
        //{
        //    switch (_mode)
        //    {
        //        case _Off:
        //            return "Nothing";
        //        case _Text:
        //            AddLetter(button);
        //            return "Nothing";
        //        case _Number:
        //            AddDigit(button);
        //            return "Nothing";
        //        default:
        //            return "Nothing";
        //    }
        //}

        //private void AddDigit(MK52_Button button)
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
        //        case ".":
        //        case "+":
        //        case "-":
        //        case "*":
        //        case "/":
        //            EntryText += button.Moniker;
        //            return;
        //        case "EE":
        //            EntryText += "E";
        //            return;
        //        case "Enter":
        //            _mode = _Off;
        //            return;
        //        case "Mode":
        //            _mode = _Text;
        //            return;
        //        case "Func K":
        //            _mode = _K;
        //            return;
        //        case "Cx":
        //            if (EntryText.Length <= 0) return;
        //            EntryText = EntryText.Substring(0, EntryText.Length-1);
        //            return;
        //        default:
        //            return;
        //    }
        //}

        //private void AddLetter( MK52_Button button)
        //{
        //    switch (button.Moniker)
        //    {
        //        case "Func F":
        //        case "Func A":
        //            return;
        //        case "Func K":
        //            _mode = _Text;
        //            return;
        //        case "Enter":
        //            _mode = _Off;
        //            return;
        //        case "Mode":
        //            _mode = _Number;
        //            return;
        //        case "Cx":
        //            if (EntryText.Length <= 0) return;
        //            EntryText = EntryText.Substring(0, EntryText.Length - 1);
        //            return;
        //        default:
        //            EntryText += "A";
        //            return;
        //    }
        //}

        ///// <summary>
        ///// Converts to human representation
        ///// </summary>
        ///// <returns></returns>
        //public override string ToString()
        //{
        //    return EntryText;
        //}
    }
}
