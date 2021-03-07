using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    /// <summary>
    /// Implements the state engine for the memory registers 
    /// In the original MK-52, there are 15 registers: 0 to E 
    /// In the Resurrect, there are 16 common registers: 0 to F and 4 loop registers L0 to L4 
    /// Registers 0 to 3 are auto-decrement, 4 to 6 are autoincrement
    /// </summary>
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

        /// <summary>
        /// In the original MK-52, the M->X does not do Bx storage!
        /// </summary>
        /// <param name="n">register number (0 to 19)</param>
        public void MtoX(int n)
        {
            //_rst.storeBx();
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
            //_rst.storeBx();
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
            //_rst.storeBx();
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
                // TODO: For compatibility, registers are converted to int!
                // Not sure, if this must be supported or changed
                //uv.fromReal(uv.toReal() + (double)delta);
                uv.fromInt(uv.toInt() + delta);
                return;
            }
        }
    }
}
