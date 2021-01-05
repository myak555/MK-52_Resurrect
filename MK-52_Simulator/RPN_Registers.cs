using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    //
    // Implements the state engine for the memory registers
    //
    public class RPN_Registers
    {
        public const int MemorySize = 16;
        public const int LoopSize = 4;

        public const int None = 0;
        public const int RegisterToStack = 1;
        public const int StackToRegister = 2;
        public const int ExtendedToStack = 3;
        public const int StackToExtended = 4;

        private const string BaseRegisterNames = "0123456789ABCDEF";
        private const string LoopRegisterNames = "L0L1L2L3";
        private int _addressMode = None;

        private RPN_Calculator _parent = null;
        private List<RPN_Value> PrimaryRegisters = new List<RPN_Value>();
        private int[] LoopRegisters = new int[LoopSize];

        public string entryResult = "";
        private bool _isActive = false;

        #region Constructors
        public RPN_Registers( RPN_Calculator parent)
        {
            _parent = parent;
            for (int i = 0; i < MemorySize; i++)
                PrimaryRegisters.Add(new RPN_Value());
            for (int i = 0; i < LoopSize; i++)
                LoopRegisters[i] = 0;
        }
        #endregion

        public bool isActive
        {
            get
            {
                return _isActive;
            }
        }

        public void ActivateEntry(int mode)
        {
            entryResult = "";
            _addressMode = mode;
            _isActive = true;
        }

        public bool onButton(RPN_Button button)
        {
            entryResult += button.Register;
            if (entryResult.Length <= 0) return false;
            switch (_addressMode)
            {
                case RegisterToStack:
                    FromRegisterToStack(entryResult);
                    break;
                case StackToRegister:
                    FromStackToRegister(entryResult);
                    break;
                case StackToExtended:
                    FromStackToMemory(entryResult);
                    break;
                case ExtendedToStack:
                    FromMemoryToStack(entryResult);
                    break;
                default:
                    break;
            }
            _isActive = false;
            _addressMode = None;
            return true;
        }

        public void AppendRegisterString()
        {
            string tmp = _parent.Program.GetCurrentLine();
            if (tmp.Length <= 0) return;
            _parent.Program.SetCurrentLine(tmp + entryResult);
        }

        #region Primary Registers
        public RPN_Value GetPrimaryRegister( string name)
        {
            int index = BaseRegisterNames.IndexOf(name);
            if (index < 0) return PrimaryRegisters[0];
            return PrimaryRegisters[index];
        }

        public void SetPrimaryRegister(string name)
        {
            int index = BaseRegisterNames.IndexOf(name);
            if (index < 0) return;
            PrimaryRegisters[index].FromRPNValue(_parent.Memory.GetCurrentLine());
        }

        public void SetPrimaryRegister(string name, string v)
        {
            SetPrimaryRegister(name, new RPN_Value(v));
        }

        public void SetPrimaryRegister(string name, RPN_Value v)
        {
            int index = BaseRegisterNames.IndexOf(name);
            if (index < 0) return;
            PrimaryRegisters[index].FromRPNValue(v);
        }

        public void SetPrimaryRegister(string name, int address)
        {
            int index = BaseRegisterNames.IndexOf(name);
            if (index < 0) return;
            PrimaryRegisters[index].FromRPNValue( _parent.Memory.GetLine(address));
        }
        public int AutoincrementPrimaryRegister(string name)
        {
            int address = -1;
            int index = BaseRegisterNames.IndexOf(name);
            if (index < 0) return address;
            address = Convert.ToInt32(PrimaryRegisters[index].asInt & 0xFFFF);
            if (index >= 7)
                return address;
            if (index <= 3) address--;
            if (index <= 6) address++;
            if (address < 0) return address;
            PrimaryRegisters[index].asInt = address;
            return address;
        }
        #endregion

        #region Loop Registers
        public int GetLoopRegister( string name)
        {
            int index = LoopRegisterNames.IndexOf(name);
            if (index < 0) return LoopRegisters[0];
            return LoopRegisters[index>>1];
        }

        public void SetLoopRegister(string name, RPN_Value v)
        {
            SetLoopRegister(name, Convert.ToInt32(v.asInt & 0xFFFFFF));
        }

        public void SetLoopRegister(string name, string v)
        {
            SetLoopRegister(name, Convert.ToInt32(v));
        }

        public void SetLoopRegister(string name, int v)
        {
            int index = LoopRegisterNames.IndexOf(name);
            if (index < 0) return;
            LoopRegisters[index>>1] = v;
        }

        //
        // Note the original MK52 stops decrement at 1, but returs zero
        //
        public int DecrementLoopRegister(int index)
        {
            int v = LoopRegisters[index] - 1;
            if (v <= 0) return v;
            LoopRegisters[index] = v;
            return LoopRegisters[index];
        }
        #endregion

        #region General Registers (both cycles and primary)
        public void FromStackToRegister(string name)
        {
            if (name.StartsWith("L"))
                SetLoopRegister(name, _parent.CalcStack.X);
            else
                SetPrimaryRegister(name, _parent.CalcStack.X);
        }
        public void FromStackToMemory(string name)
        {
            int address = (name.StartsWith("L"))?
                GetLoopRegister(name):
                AutoincrementPrimaryRegister(name);
            if (address < 0) return;
            if (address >= _parent.Memory.Counter.MaxValue) return;
            _parent.Memory.FromStack( address);
            _parent.Memory.Counter.Set(address);
        }
        public void FromRegisterToStack(string name)
        {
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.Push();
            if (name.StartsWith("L"))
                _parent.CalcStack.X.asInt = GetLoopRegister(name);
            else
                _parent.CalcStack.X.FromRPNValue( GetPrimaryRegister(name));
        }
        public void FromMemoryToStack(string name)
        {
            int address = (name.StartsWith("L")) ?
                GetLoopRegister(name) :
                AutoincrementPrimaryRegister(name);
            if (address < 0) return;
            if (address >= _parent.Memory.Counter.MaxValue) return;
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.Push();
            _parent.Memory.ToStack(address);
            _parent.Memory.Counter.Set(address);
        }
        #endregion

        #region Load / Save
        public bool LoadLine(string s)
        {
            if (s.StartsWith("Reg_L"))
            {
                SetLoopRegister(s.Substring(4, 2), s.Substring(8).Trim());
                return true;
            }
            if (s.StartsWith("Reg_"))
            {
                SetPrimaryRegister(s.Substring(4, 1), s.Substring(7).Trim());
                return true;
            }
            return false;
        }

        public void Save(StreamWriter sw)
        {
            sw.Write("#\n");
            sw.Write("# Primary Registers:\n");
            sw.Write("#\n");
            for (int i = 0; i < PrimaryRegisters.Count; i++)
            {
                RPN_Value v = PrimaryRegisters[i];
                if (v.isEmpty) continue;
                sw.Write(i.ToString("Reg_") + BaseRegisterNames[i] + " = " + v.ToString() + "\n");
            }
            sw.Write("#\n");
            sw.Write("# Loop Registers:\n");
            sw.Write("#\n");
            for (int i = 0; i < LoopRegisters.Length; i++)
            {
                int v = LoopRegisters[i];
                if (v==0) continue;
                sw.Write(i.ToString("Reg_L") + BaseRegisterNames[i] + " = " + v.ToString() + "\n");
            }
        }
        #endregion
    }
}
