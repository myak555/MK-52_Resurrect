using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    //
    // Implements the state engine for the memory registers
    //
    public class Register_Memory
    {
        private const string _RM_NameConversion = "0123456789ABCDEFL";
        public const int REGISTER_MEMORY_SIZE = 180;
        public const int REGISTER_MEMORY_NVALS = 20;
        public const int RPN_REGISTER_L0 = 16;
        public const int RPN_REGISTER_L1 = 17;
        public const int RPN_REGISTER_L2 = 18;
        public const int RPN_REGISTER_L3 = 19;

        private MK52_Host _parent = null;
        private RPN_Stack _rst = null;
        private Extended_Memory _emem = null;
        private List<UniversalValue> m_Values = new List<UniversalValue>();

        public void init( MK52_Host components)
        {
            _parent = components;
            _rst = _parent._m_RPN_Stack;
            _emem = _parent._m_Extended_Memory;
            for (int i = 0; i < REGISTER_MEMORY_NVALS; i++)
                m_Values.Add(new UniversalValue());
            clear();
        }

        public void clear()
        {
            for (int i = 0; i < REGISTER_MEMORY_NVALS; i++)
                m_Values[i].fromInt(0);
        }

        public void MtoX(int n)
        {
            _rst.storeBx();
            _rst.push();
            if (n < 0 || n >= REGISTER_MEMORY_NVALS)
            {
                _rst.X.fromInt(0);
                return;
            }
            _rst.X.fromLocation(_registerAddress(n));
        }

        public void XtoM(int n)
        {
            if (n < 0 || n >= REGISTER_MEMORY_NVALS) return;
            UniversalValue uv = _registerAddress(n);
            if (n < 16)
                uv.fromLocation(_rst.X);
            else
                uv.fromInt(_rst.X.toInt());
        }

        public void K_MtoX(int n)
        {
            _rst.storeBx();
            _rst.push();
            if (n < 0 || n >= REGISTER_MEMORY_NVALS) return;
            UniversalValue uv = _registerAddress(n);
            if (uv.isEmpty())
            {
                _rst.X.fromInt(0);
                return;
            }
            Int64 index = uv.toInt();
            _autoIncrement(n, uv);
            if (index < 0 || index >= Extended_Memory.EXTENDED_MEMORY_NVALS)
            {
                _rst.X.fromInt(0);
                return;
            }
            index = index % 10000;
            _emem.setCounter((uint)index);
            _emem.toUV(_rst.X);
            if (_rst.X.isEmpty()) _rst.X.fromInt(0);
        }

        public void K_XtoM(int n)
        {
            if (n < 0 || n >= REGISTER_MEMORY_NVALS) return;
            UniversalValue uv = _registerAddress(n);
            if (uv.isEmpty()) return;
            Int64 index = uv.toInt();
            _autoIncrement(n, uv);
            A_XtoM(index);
        }

        public void A_MtoX(Int64 index)
        {
            _rst.storeBx();
            _rst.push();
            if (index < 0 || index >= Extended_Memory.EXTENDED_MEMORY_NVALS)
            {
                _rst.X.fromInt(0);
                return;
            }
            index = index % 10000;
            _emem.setCounter((uint)index);
            _emem.toUV(_rst.X);
            if (_rst.X.isEmpty()) _rst.X.fromInt(0);
        }

        public void A_XtoM(Int64 index)
        {
            if (index < 0 || index >= Extended_Memory.EXTENDED_MEMORY_NVALS)
            {
                _rst.setStackLabel_P(0, "No such address");
                return;
            }
            index = index % 10000;
            _emem.setCounter((uint)index);
            _emem.fromUV(_rst.X);
        }

        public int registerByName( string name)
        {
            int index = _chrfind_P( name[0]);
            if (index < 0) return -1;
            if (index < 16) return index;
            index = _chrfind_P(name[1]);
            if (index < 0) return -1;
            if (index >= 4) return -1;
            return index + 16;
        }

        public UniversalValue _registerAddress( int n)
        {
           return m_Values[n];
        }

        public void MtoX(string name)
        {
            MtoX( registerByName(name));
        }

        public void XtoM(string name)
        {
            XtoM( registerByName(name));
        }

        public void K_MtoX(string name)
        {
            K_MtoX( registerByName(name));
        }

        public void K_XtoM(string name)
        {
            K_XtoM( registerByName(name));
        }

        public void A_MtoX(string address)
        {
            _rst.storeBx();
            _rst.push();
            _emem.setCounter(address);
            _emem.toUV(_rst.X);
            if (_rst.X.isEmpty()) _rst.X.fromInt(0);
        }

        public void A_XtoM(string address)
        {
            _emem.setCounter(address);
            _emem.fromUV(_rst.X);
        }

        /// <summary>
        /// Alias for C++ implementation
        /// </summary>
        private int _chrfind_P(char c)
        {
            return _RM_NameConversion.IndexOf(c);
        }

        private void _autoIncrement( int n, UniversalValue uv)
        {
            if (n < 0) return;
            if (n > 6) return;
            int delta = (n > 3) ? 1 : -1;
            if (uv.isInt())
            {
                uv.fromInt(uv.toInt() + delta);
                return;
            }
            if (uv.isReal())
            {
                uv.fromReal(uv.toReal() + (double)delta);
                return;
            }
        }

        //public void ActivateEntry(int mode)
        //{
        //    entryResult = "";
        //    _addressMode = mode;
        //    _isActive = true;
        //}

        //public bool onButton(MK52_Button button)
        //{
        //    //entryResult += button.Register;
        //    //if (entryResult.Length <= 0) return false;
        //    //switch (_addressMode)
        //    //{
        //    //    case RegisterToStack:
        //    //        FromRegisterToStack(entryResult);
        //    //        break;
        //    //    case StackToRegister:
        //    //        FromStackToRegister(entryResult);
        //    //        break;
        //    //    case StackToExtended:
        //    //        FromStackToMemory(entryResult);
        //    //        break;
        //    //    case ExtendedToStack:
        //    //        FromMemoryToStack(entryResult);
        //    //        break;
        //    //    default:
        //    //        break;
        //    //}
        //    //_isActive = false;
        //    //_addressMode = None;
        //    return true;
        //}

        //public void AppendRegisterString()
        //{
        //    string tmp = _parent.Program.GetCurrentLine();
        //    if (tmp.Length <= 0) return;
        //    _parent.Program.SetCurrentLine(tmp + entryResult);
        //}

        //#region Primary Registers
        //public RPN_Value GetPrimaryRegister( string name)
        //{
        //    int index = BaseRegisterNames.IndexOf(name);
        //    if (index < 0) return PrimaryRegisters[0];
        //    return PrimaryRegisters[index];
        //}

        //public void SetPrimaryRegister(string name)
        //{
        //    int index = BaseRegisterNames.IndexOf(name);
        //    if (index < 0) return;
        //    PrimaryRegisters[index].FromRPNValue(_parent.Memory.GetCurrentLine());
        //}

        //public void SetPrimaryRegister(string name, string v)
        //{
        //    SetPrimaryRegister(name, new RPN_Value(v));
        //}

        //public void SetPrimaryRegister(string name, RPN_Value v)
        //{
        //    int index = BaseRegisterNames.IndexOf(name);
        //    if (index < 0) return;
        //    PrimaryRegisters[index].FromRPNValue(v);
        //}

        //public void SetPrimaryRegister(string name, int address)
        //{
        //    int index = BaseRegisterNames.IndexOf(name);
        //    if (index < 0) return;
        //    PrimaryRegisters[index].FromRPNValue( _parent.Memory.GetLine(address));
        //}
        //public int AutoincrementPrimaryRegister(string name)
        //{
        //    int address = -1;
        //    int index = BaseRegisterNames.IndexOf(name);
        //    if (index < 0) return address;
        //    address = Convert.ToInt32(PrimaryRegisters[index].asInt & 0xFFFF);
        //    if (index >= 7)
        //        return address;
        //    if (index <= 3) address--;
        //    if (index <= 6) address++;
        //    if (address < 0) return address;
        //    PrimaryRegisters[index].asInt = address;
        //    return address;
        //}
        //#endregion

        //#region Loop Registers
        //public int GetLoopRegister( string name)
        //{
        //    int index = LoopRegisterNames.IndexOf(name);
        //    if (index < 0) return LoopRegisters[0];
        //    return LoopRegisters[index>>1];
        //}

        //public void SetLoopRegister(string name, RPN_Value v)
        //{
        //    SetLoopRegister(name, Convert.ToInt32(v.asInt & 0xFFFFFF));
        //}

        //public void SetLoopRegister(string name, string v)
        //{
        //    SetLoopRegister(name, Convert.ToInt32(v));
        //}

        //public void SetLoopRegister(string name, int v)
        //{
        //    int index = LoopRegisterNames.IndexOf(name);
        //    if (index < 0) return;
        //    LoopRegisters[index>>1] = v;
        //}

        ////
        //// Note the original MK52 stops decrement at 1, but returs zero
        ////
        //public int DecrementLoopRegister(int index)
        //{
        //    int v = LoopRegisters[index] - 1;
        //    if (v <= 0) return v;
        //    LoopRegisters[index] = v;
        //    return LoopRegisters[index];
        //}
        //#endregion

        //#region General Registers (both cycles and primary)
        //public void FromStackToRegister(string name)
        //{
        //    //if (name.StartsWith("L"))
        //    //    SetLoopRegister(name, _parent.CalcStack.X);
        //    //else
        //    //    SetPrimaryRegister(name, _parent.CalcStack.X);
        //}
        //public void FromStackToMemory(string name)
        //{
        //    int address = (name.StartsWith("L"))?
        //        GetLoopRegister(name):
        //        AutoincrementPrimaryRegister(name);
        //    if (address < 0) return;
        //    if (address >= _parent.Memory.Counter.MaxValue) return;
        //    _parent.Memory.FromStack( address);
        //    _parent.Memory.Counter.Set(address);
        //}
        //public void FromRegisterToStack(string name)
        //{
        //    //_parent.CalcStack.StorePreviousValue();
        //    //_parent.CalcStack.Push();
        //    //if (name.StartsWith("L"))
        //    //    _parent.CalcStack.X.asInt = GetLoopRegister(name);
        //    //else
        //    //    _parent.CalcStack.X.FromRPNValue( GetPrimaryRegister(name));
        //}
        //public void FromMemoryToStack(string name)
        //{
        //    //int address = (name.StartsWith("L")) ?
        //    //    GetLoopRegister(name) :
        //    //    AutoincrementPrimaryRegister(name);
        //    //if (address < 0) return;
        //    //if (address >= _parent.Memory.Counter.MaxValue) return;
        //    //_parent.CalcStack.StorePreviousValue();
        //    //_parent.CalcStack.Push();
        //    //_parent.Memory.ToStack(address);
        //    //_parent.Memory.Counter.Set(address);
        //}
        //#endregion

        //#region Load / Save
        //public bool LoadLine(string s)
        //{
        //    if (s.StartsWith("Reg_L"))
        //    {
        //        SetLoopRegister(s.Substring(4, 2), s.Substring(8).Trim());
        //        return true;
        //    }
        //    if (s.StartsWith("Reg_"))
        //    {
        //        SetPrimaryRegister(s.Substring(4, 1), s.Substring(7).Trim());
        //        return true;
        //    }
        //    return false;
        //}

        //public void Save(StreamWriter sw)
        //{
        //    sw.Write("#\n");
        //    sw.Write("# Primary Registers:\n");
        //    sw.Write("#\n");
        //    for (int i = 0; i < PrimaryRegisters.Count; i++)
        //    {
        //        RPN_Value v = PrimaryRegisters[i];
        //        if (v.isEmpty) continue;
        //        sw.Write(i.ToString("Reg_") + BaseRegisterNames[i] + " = " + v.ToString() + "\n");
        //    }
        //    sw.Write("#\n");
        //    sw.Write("# Loop Registers:\n");
        //    sw.Write("#\n");
        //    for (int i = 0; i < LoopRegisters.Length; i++)
        //    {
        //        int v = LoopRegisters[i];
        //        if (v==0) continue;
        //        sw.Write(i.ToString("Reg_L") + BaseRegisterNames[i] + " = " + v.ToString() + "\n");
        //    }
        //}
        //#endregion
    }
}
