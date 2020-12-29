using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class RPN_Counter
    {
        private const string AddressSymbols = "0123456789";
        private int _value = 0;
        private string EditAddress = "";
        private bool _isActive = false;

        public string Name = "PC";
        public int MaxValue = 1000;
        public int entryResult = 0;
 
        public RPN_Counter( string name, int maxValue)
        {
            Name = name;
            MaxValue = maxValue;
        }

        public override string ToString()
        {
            if (_isActive) return Name + "=" + EditAddress.PadLeft(3);
            return Name + "=" +_value.ToString("000");
        }

        /// <summary>
        /// Clears the entry, resets the mode;
        /// </summary>
        public void Clear()
        {
            EditAddress = "";
            _isActive = false;
        }

        public int V
        {
            get
            {
                return _value;
            }
        }

        public bool isActive
        {
            get
            {
                return _isActive;
            }
        }

        public void ActivateEntry()
        {
            _isActive = true;
        }

        public void Decrement()
        {
            _value--;
            _clip();
        }

        public void Increment()
        {
            _value++;
            _clip();
        }

        public void Set(int v)
        {
            _value = v;
            _clip();
        }

        public void Set(string s)
        {
            try
            {
                _value = Convert.ToInt32(s);
            }
            catch
            {
            }
            finally
            {
                _clip();
            }
        }

        public void SetEditAddress()
        {
            EditAddress = _value.ToString();
        }

        public bool isNewAddress
        {
            get
            {
                return entryResult != _value;
            }
        }

        public void resetAddress()
        {
            _value = entryResult;
        }

        /// <summary>
        /// Adds an entry to the address
        /// </summary>
        /// <param name="text"></param>
        /// <returns>true if entry is completed</returns>
        public bool AddDigitToAddress(string text, bool setCounter)
        {
            if (text == "Enter")
            {
                _setPoiterToAddress( setCounter);
                return true;
            }
            for (int i = 0; i < text.Length; i++)
            {
                char c = text[i];
                if (AddressSymbols.IndexOf(c) < 0) continue;
                EditAddress += c;
            }
            if (EditAddress.Length < 3) return false;
            _setPoiterToAddress(setCounter);
            return true;
        }

        private void _setPoiterToAddress( bool set)
        {
            entryResult = _value;
            if (EditAddress.Length > 0)
            {
                entryResult = Convert.ToInt32(EditAddress);
                if (entryResult < 0) entryResult = MaxValue - 1;
                if (entryResult >= MaxValue) entryResult = 0;
                if (set) Set(entryResult);
            }
            Clear();
        }

        private void _clip()
        {
            if (_value < 0) _value = MaxValue - 1;
            if (_value >= MaxValue) _value = 0;
        }
    }
}
