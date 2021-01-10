using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator.Receivers
{
    //
    // Implements an unsigned integer entry
    //
    public class InputReceiver_Address : RPN_InputReceiver
    {        
        private const bool _Off = false;
        private const bool _On = true;
        private bool _mode = _Off;
        
        // fields used for entry editing
        public string Entry = "";

        /// <summary>
        /// Constructor
        /// </summary>
        public InputReceiver_Address(RPN_Calculator parent):
            base( parent)
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
            Entry = "";
            _mode = _Off;
        }

        public void Activate()
        {
            _mode = _On;
        }

        /// <summary>
        /// Called by the hardware button processing
        /// </summary>
        /// <param name="button">Button pressed</param>
        public override void onButton(RPN_Button button)
        {
            switch (button.Moniker)
            {
                case "0":
                case "1":
                case "2":
                case "3":
                case "4":
                case "5":
                case "6":
                case "7":
                case "8":
                case "9":
                    AddDigit(button.Moniker);
                    return;
                case "Cx":
                    AddCx();
                    return;
                default:
                    return;
            }
        }

        /// <summary>
        /// Returns "TO?" if the receiver is active
        /// </summary>
        public override string DisplayName
        {
            get
            {
                if ( isActive) return "TO?";
                return "   ";
            }
        }

        /// <summary>
        /// Returns numeric representanion, resets entry
        /// </summary>
        public int getV( int previousV)
        {
            if (Entry.Length >= 1) previousV = Convert.ToInt32(Entry);
            Clear();
            return previousV;
        }

        /// <summary>
        /// Returns true if entry is 3 digits
        /// </summary>
        public bool isComplete
        {
            get
            {
                return Entry.Length == 3;
            }
        }

        /// <summary>
        /// Converts to human representation
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Entry.PadLeft( 3);
        }

        #region Private Functions
        private void AddDigit(string key)
        {
            _mode = _On;
            Entry += key;
            while (Entry.Length > 3) Entry = Entry.Substring(1);
        }
        private void AddCx()
        {
            int l = Entry.Length;
            if (l <= 0) return;
            Entry = Entry.Substring(0, l - 1);
        }
        #endregion
    }
}