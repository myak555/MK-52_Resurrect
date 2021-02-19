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
using System.IO;

namespace MK52Simulator
{
    //
    // Implements program storage (as prototype)
    // The actual code on C++ will be without Dictionary
    //
    public class Extended_Memory
    {
        public const int EXTENDED_MEMORY_SIZE  = 36000;
        public const int EXTENDED_MEMORY_NVALS = 4000;
        private MK52_Host _parent = null;
        private Dictionary<uint, UniversalValue> _buffer = new Dictionary<uint, UniversalValue>();
        private UniversalValue _uv = new UniversalValue();
        private uint _counter = 0;

        public void init( MK52_Host components)
        {
            _parent = components;
        }

        public void clear()
        {
            _buffer.Clear();
            resetCounter();
        }

        public void clearCurrent()
		{
            if(!_buffer.ContainsKey( _counter)) return;
            _buffer.Remove( _counter);
		}

        public void resetCounter()
		{
            _counter = 0;
		}

        public uint getCounter()
        {
            return _counter;
        }

		public uint setCounter(uint address)
		{
            if( address >= EXTENDED_MEMORY_NVALS) address = EXTENDED_MEMORY_NVALS-1;
            _counter = address;  
            return _counter;
		}
		
		public uint setCounter(string text)
        {
            int ln = text.Length;
            if (ln <= 0) return _counter;
            if (text[0] == ' ') return _counter;
            return setCounter( Convert.ToUInt32(text.Trim()));
		}

        public bool incrementCounter()
        {
            if (_counter >= EXTENDED_MEMORY_NVALS - 1) return true;
            _counter++;
            return false;
		}
		
		public bool decrementCounter()
		{
            if (_counter == 0) return true;
            _counter--;
            return false;
		}

        public UniversalValue getCurrentLine()
		{
            return getLine(_counter);
		}

        public UniversalValue getLine( uint n)
		{
            if (_buffer.ContainsKey(n)) return _buffer[n];
            return new UniversalValue();
        }

        public string toString( string text, int n)
		{
            if (n < 0 || EXTENDED_MEMORY_NVALS <= n) return " ";
            StringBuilder sb = new StringBuilder(n.ToString("0000"));
            sb.Append( (n == _counter)? "> " : "  ");
            sb.Append( _memoryAddress(n).toString());
            return sb.ToString();
		}

		public void fromString( string text)
        {
            _uv.fromString(text);
            fromUV( _uv);
        }

        public UniversalValue getTemporaryUV()
		{
			return _uv;
		}
		
        public void fromUV( UniversalValue uv)
        {
            bool exists = _buffer.ContainsKey(_counter);
            if (uv.isEmpty() && exists)
            {
                _buffer.Remove(_counter);
                return;
            }
            if (!exists)
            {
                _buffer.Add(_counter, new UniversalValue());
            }
            _buffer[_counter].fromLocation(uv);
        }

        public void toUV( UniversalValue uv)
        {
            bool exists = _buffer.ContainsKey(_counter);
            if (!exists)
            {
                uv.fromEmpty();
                return;
            }
            uv.fromLocation( _buffer[_counter]);
        }

        public void swapWithUV( UniversalValue uv)
        {
            _uv.fromLocation(uv.toBytes());
            toUV(uv);
            fromUV(_uv);
        }

        private UniversalValue _memoryAddress( int index)
		{
           return getLine((uint)index);
		}
        
        //public bool LoadLine(string s)
        //{
        //    if (!s.StartsWith("M")) return false;
        //    if (MCLoadHelper(s)) return true;
        //    int number = Convert.ToInt32(s.Substring(1, 3));
        //    SetLine( number, new RPN_Value( s.Substring(5).Trim()));
        //    return true;
        //}

        //public bool Load(StreamReader sr)
        //{
        //    ExtendedMemory.Clear();
        //    while( !sr.EndOfStream)
        //    {
        //        string s = sr.ReadLine().Trim();
        //        if( s.Length == 0 || s.StartsWith("#")) continue;
        //        LoadLine(s);
        //    }
        //    return true;
        //}

        //public void Save(StreamWriter sw)
        //{
        //    sw.Write("#\n");
        //    sw.Write("# Extended Memory:\n");
        //    sw.Write("#\n");
        //    sw.Write("MC = " + Counter.V.ToString() + "\n");
        //    for (int k = 0; k < Counter.MaxValue; k++)
        //    {
        //        if (!ExtendedMemory.ContainsKey(k)) continue;
        //        RPN_Value v = ExtendedMemory[k];
        //        if (v.isEmpty) continue;
        //        sw.Write(k.ToString("M000: ") + v.ToString() + "\n");
        //    }
        //}

        //private bool MCLoadHelper(string s)
        //{
        //    if (!s.StartsWith("MC = ")) return false;
        //    Counter.Set(Convert.ToInt32(s.Substring(5).Trim()));
        //    return true;
        //}
    }
}
