using System;
using System.Collections.Generic;
using System.Text;
using MK52Simulator.Receivers;

namespace MK52Simulator
{
    public class RPN_Counter
    {
        private int _value = 0;
        private InputReceiver_Address _ira = new InputReceiver_Address(null); 

        //private const string AddressSymbols = "0123456789";
        //private string EditAddress = "";
        //private bool _isActive = false;
        private bool _isNewAddress = false;

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
            string tmp = (_ira.isActive)? _ira.ToString() : _value.ToString("000");
            return Name + "=" + tmp;
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
                return _ira.isActive;
            }
        }

        public void ActivateEntry()
        {
            _ira.Activate();
            _isNewAddress = false;
        }

        public string ActiveEntry
        {
            get
            {
                return _ira.Entry;
            }
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
            _ira.Entry = _value.ToString();
        }

        public bool isNewAddress
        {
            get
            {
                return _isNewAddress;
            }
        }

        public void resetAddress()
        {
            _value = entryResult;
        }

        /// <summary>
        /// Adds an entry to the address
        /// </summary>
        /// <returns>true if entry is completed</returns>
        public bool onButton(RPN_Button button, bool setCounter)
        {
            if (button.Moniker == "Enter")
            {
                _setPoiterToAddress(setCounter);
                return true;
            }
            _ira.onButton(button);
            _isNewAddress = true;
            if (!_ira.isComplete) return false;
            _setPoiterToAddress(setCounter);
            return true;
        }

        private void _setPoiterToAddress( bool set)
        {
            entryResult = _ira.getV( _value);
            if (entryResult < 0) entryResult = MaxValue - 1;
            if (entryResult >= MaxValue) entryResult = 0;
            if (set) Set(entryResult);
        }

        private void _clip()
        {
            if (_value < 0) _value = MaxValue - 1;
            if (_value >= MaxValue) _value = 0;
        }
    }
}
