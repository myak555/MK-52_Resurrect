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

        private const string BaseRegisterNames = "0123456789ABCDEF";
        private const string LoopRegisterNames = "L0L1L2L3";

        private RPN_Calculator _parent = null;
        private List<RPN_Value> PrimaryRegisters = new List<RPN_Value>();
        private int[] LoopRegisters = new int[LoopSize];

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
        #endregion

        #region Loop Registers
        public int GetLoopRegister(string name)
        {
            int index = LoopRegisterNames.IndexOf(name);
            if (index < 0) return LoopRegisters[0];
            return LoopRegisters[index>>1];
        }

        public void SetLoopRegister(string name, RPN_Value v)
        {
            SetLoopRegister(name, Convert.ToInt32(v.asInt));
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
