using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    //
    // Implements program storage (as prototype)
    // The actual code on C++ will be without Dictionary
    //
    public class RPN_Memory
    {
        public const int ExtendedMemorySize = 1000;
        public const int SetAddressOnly = 0;
        public const int MemoryToStack = 1;
        public const int StackToMemory = 2;
        private int _addressMode = SetAddressOnly;

        private MK52_Host _parent = null;
        private Dictionary<int, RPN_Value> ExtendedMemory = new Dictionary<int, RPN_Value>();

        public RPN_Counter Counter = new RPN_Counter("MC", ExtendedMemorySize);

        public RPN_Memory( MK52_Host parent)
        {
            _parent = parent;
        }

        public void Clear()
        {
            ExtendedMemory.Clear();
            Counter.Set(0);
        }

        public void ToStrings(string[] inp)
        {
        //    for (int i = -7, j = 1; j <= 8; i++, j++)
        //    {
        //        int dl = Counter.V + i;
        //        inp[j] = "";
        //        if (dl < 0) continue;
        //        if (dl >= ProgramSize) continue;
        //        StringBuilder sb = new StringBuilder();
        //        sb.Append(dl.ToString("000"));
        //        sb.Append((i == 0) ? "> " : "  ");
        //        if (j < 8)
        //        {
        //            sb.Append(GetLine(dl));
        //            inp[j] = sb.ToString();
        //            continue;
        //        }
        //        if (Number.isActive)
        //        {
        //            sb.Append(Number.ToString());
        //            inp[j] = sb.ToString();
        //            continue;
        //        }
        //        if (Counter.isActive)
        //        {
        //            sb.Append(GetLine(dl));
        //            sb.Append(Counter.ActiveEntry);
        //            inp[j] = sb.ToString();
        //            continue;
        //        }
        //        sb.Append(GetLine(dl));
        //        inp[j] = sb.ToString();
        //    }
        }

        //public bool isAddressEntry
        //{
        //    get
        //    {
        //        return Counter.isActive;
        //    }
        //}

        public void ActivateEntry( int mode)
        {
            _addressMode = mode;
            Counter.ActivateEntry();
        }

        public void onButton(RPN_Button button)
        {
            if (!Counter.onButton( button, false)) return;
            switch (_addressMode)
            {
                case MemoryToStack:
                    if (Counter.isNewAddress)
                    {
                        Counter.resetAddress();
                        ToStack( Counter.V);
                        return;
                    }
                    Counter.Decrement();
                    ToStack(Counter.V);
                    return;
                case StackToMemory:
                    if (Counter.isNewAddress)
                    {
                        Counter.resetAddress();
                        FromStack(Counter.V);
                        return;
                    }
                    FromStack(Counter.V);
                    Counter.Increment();
                    return;
                default:
                    Counter.Set(Counter.entryResult);
                    return;
            }
        }

        public RPN_Value GetCurrentLine()
        {
            return GetLine( Counter.V);
        }

        public RPN_Value GetLine(int address)
        {
            if (!ExtendedMemory.ContainsKey(address)) return new RPN_Value(); // empty object
            return ExtendedMemory[address];
        }

        public void SetLine(int address, RPN_Value v)
        {
            if (v.isEmpty)
            {
                if (ExtendedMemory.ContainsKey(address))
                    ExtendedMemory.Remove(address);
                return;
            }
            if (!ExtendedMemory.ContainsKey(address))
            {
                ExtendedMemory.Add(address, v);
                return;
            }
            ExtendedMemory[address].FromRPNValue( v);
        }

        public void FromStack( int address)
        {
            RPN_Value dest = GetLine(address);
            dest.FromRPNValue(_parent.CalcStack.X);
            SetLine(address, dest);
        }

        public void ToStack(int address)
        {
            RPN_Value src = GetLine(address);
            RPN_Value dest = _parent.CalcStack.X;
            _parent.CalcStack.StorePreviousValue();
            _parent.CalcStack.Push(1);
            dest.FromRPNValue(src);
        }
        
        public bool LoadLine(string s)
        {
            if (!s.StartsWith("M")) return false;
            if (MCLoadHelper(s)) return true;
            int number = Convert.ToInt32(s.Substring(1, 3));
            SetLine( number, new RPN_Value( s.Substring(5).Trim()));
            return true;
        }

        public bool Load(StreamReader sr)
        {
            ExtendedMemory.Clear();
            while( !sr.EndOfStream)
            {
                string s = sr.ReadLine().Trim();
                if( s.Length == 0 || s.StartsWith("#")) continue;
                LoadLine(s);
            }
            return true;
        }

        public void Save(StreamWriter sw)
        {
            sw.Write("#\n");
            sw.Write("# Extended Memory:\n");
            sw.Write("#\n");
            sw.Write("MC = " + Counter.V.ToString() + "\n");
            for (int k = 0; k < Counter.MaxValue; k++)
            {
                if (!ExtendedMemory.ContainsKey(k)) continue;
                RPN_Value v = ExtendedMemory[k];
                if (v.isEmpty) continue;
                sw.Write(k.ToString("M000: ") + v.ToString() + "\n");
            }
        }

        private bool MCLoadHelper(string s)
        {
            if (!s.StartsWith("MC = ")) return false;
            Counter.Set(Convert.ToInt32(s.Substring(5).Trim()));
            return true;
        }
    }
}
