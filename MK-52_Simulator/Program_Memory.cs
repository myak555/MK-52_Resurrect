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
    public class Program_Memory
    {
        public const int EMODE_OWERWRITE = 0;
        public const int EMODE_INSERT = 1;
        public const int EMODE_SHIFT = 2;
        public const int PROGRAM_MEMORY_SIZE = 64000;
        public const int RETURN_STACK_SIZE = 100;

        private uint _counter = 0;
        private uint _bottom = 1;
        private uint _current = 0;
        private byte[] _buffer = new byte[PROGRAM_MEMORY_SIZE];
        private MK52_Host _parent = null;

        private int _eMode = EMODE_OWERWRITE;
        private string[] _emodeLabels = { "OVR", "INS", "SHF" };

        private uint[] _returnStack_ptrs = new uint[RETURN_STACK_SIZE];
        private uint[] _returnStack_ctrs = new uint[RETURN_STACK_SIZE];
        private int _returnStackPtr = 0;

        public void init( MK52_Host components)
        {
            _parent = components;
            clear();
            setEMode(EMODE_OWERWRITE);

            // TODO
            setCounter(3);
            replaceLine_P("This is a test.");
            string s = getCurrentLine();
            decrementCounter();
            s = getCurrentLine();
            replaceLine_P("Alice in Wonderland!");
            s = getCurrentLine();
            incrementCounter();
            s = getCurrentLine();
        }

        public void clear()
        {
            for( int i=0; i<_buffer.Length; i++)
                _buffer[i] = 0;
            _bottom = 1; // one empty line
            resetCounter();
        }

        public void resetCounter()
        {
            _current = 0;
            _counter = 0;
            _returnStackPtr = 0;
        }

        public uint getCounter()
        {
            return _counter;
        }

        public uint setCounter(uint address)
        {
            while (_counter < address)
            {
                if (incrementCounter()) break;
            }
            while (_counter > address)
            {
                if (decrementCounter()) break;
            }
            return _counter;
        }

        public uint setCounter(string text)
        {
            int ln = text.Length;
            if (ln <= 0) return _counter;
            if (text[0] == ' ') return _counter;
            return setCounter(Convert.ToUInt32(text.Trim()));
        }

        public bool incrementCounter()
        {
            // Skip to end of line
            uint tmp = _current;
            while (_current < PROGRAM_MEMORY_SIZE && currentChar() != 0) _current++;

            // End of memory reached - nothing changes
            if (_current >= PROGRAM_MEMORY_SIZE)
            {
                _current = tmp;
                return true;
            }
            _current++; // next line
            _counter++;
            return false;
        }

        public bool decrementCounter()
        {
            if (_current == 0) return true; // already at top

            // Skip to end of previous line
            int tmp = (int)_current;
            tmp--;
            if (tmp <= 0)
            {
                _counter = 0;
                _current = 0;
                return false;
            }

            // Skip to beginning of previous line
            tmp--;
            while (tmp >= 0 && _buffer[tmp] != 0) tmp--;
            if (tmp < 0)
            {
                _counter = 0;
                _current = 0;
                return false;
            }
            _current = Convert.ToUInt32( tmp + 1);
            _counter--;
            return false;
        }

        public bool goSub( uint address)
        {
            if (_returnStackPtr >= RETURN_STACK_SIZE) return true;
            _returnStack_ptrs[_returnStackPtr] = _current;
            _returnStack_ctrs[_returnStackPtr] = _counter;
            _returnStackPtr++;
            setCounter(address);
            return false;
        }

        public bool goSub( string text)
        {
            if (_returnStackPtr >= RETURN_STACK_SIZE) return true;
            _returnStack_ptrs[_returnStackPtr] = _current;
            _returnStack_ctrs[_returnStackPtr] = _counter;
            _returnStackPtr++;
            setCounter(text);
            return false;
        }

        public bool returnFromSub()
        {
            if (_returnStackPtr == 0) return true;
            _returnStackPtr--;
            _current = _returnStack_ptrs[_returnStackPtr];
            _counter = _returnStack_ctrs[_returnStackPtr];
            incrementCounter(); // go to the next line after call
            return false;
        }

        public uint getFree()
        {
            return (uint)(PROGRAM_MEMORY_SIZE-_bottom);
        }

        public string getCurrentLine()
        {
            StringBuilder sb = new StringBuilder();
            for( uint i=_current; _buffer[i]!=0; i++)
                sb.Append( (char)_buffer[i]);            
            return sb.ToString();
        }

        public char currentChar()
        {
            return (char)_buffer[_current];
        }

        public bool isAtEnd()
        {
            return _current >= _bottom;
        }

        public bool appendLine(string line)
        {
            return appendLine_P( line);
        }

        public bool appendLine_P(string line)
        {
            int toAppend = line.Length+1;
            if (_current + toAppend >= PROGRAM_MEMORY_SIZE) return true; // no space
            _bottom = _current;
            toAppend--;
            for (int i = 0; i < toAppend; i++, _bottom++)
                _buffer[_bottom] = Convert.ToByte( line[i]);
            _buffer[_bottom] = 0;
            return false;
        }

        public bool replaceLine(string line)
        {
            return replaceLine_P( line);
        }

        private bool __copyStringToCurrent(string line)
        {
            uint j = _current;
            for (int i = 0; i < line.Length; i++, j++)
                _buffer[j] = Convert.ToByte(line[i]);
            _buffer[j] = 0;
            return false;
        }

        private bool __moveStringsFromCurrent(int shift)
        {
            if (shift > 0)
            {
                if (_bottom + (uint)shift >= PROGRAM_MEMORY_SIZE) return true;
                for (int i = (int)_bottom; i >= _current; i--)
                    _buffer[i + shift] = _buffer[i];
                _bottom += (uint)shift;
            }
            if (shift < 0)
            {
                for (int i = (int)_current-shift; i <= _bottom; i++)
                    _buffer[i+shift] = _buffer[i];
                for (int i = shift; i <= 0; i++, _bottom--)
                    _buffer[_bottom] = 0;
            }
            return false;
        }

        public bool replaceLine_P(string line)
        {
            if (_current >= _bottom) return appendLine_P(line);
            int toCopy = line.Length + 1;
            string ptrC = getCurrentLine();
            int toReplace = ptrC.Length + 1;
            if( __moveStringsFromCurrent(toCopy - toReplace)) return true;
            return __copyStringToCurrent(line);
        }

        public bool insertLine(string line)
        {
            return insertLine_P(line);
        }

        public bool insertLine_P( string line)
        {
            if (_current >= _bottom) return appendLine_P(line);
            int toInsert = line.Length + 1;
            if (__moveStringsFromCurrent(toInsert)) return true;
            return __copyStringToCurrent(line);
        }

        public bool updateLine(string line)
        {
            return updateLine_P( line);
        }

        public bool updateLine_P( string line)
        {
            if (_eMode == EMODE_OWERWRITE) return replaceLine_P(line);
            else return insertLine_P(line);
        }

        public void deleteLine()
        {
            if (_current >= _bottom) return;
            string s = getCurrentLine();
            __moveStringsFromCurrent( -s.Length );
        }

        public bool commentLine()
        {
            if( _current >= _bottom)
                return appendLine_P("#");
            string ptrC = getCurrentLine();
            if( ptrC.StartsWith("#")) return __moveStringsFromCurrent(-1);
            if( __moveStringsFromCurrent( 1 )) return true;
            _buffer[_current] = Convert.ToByte('#');
            return false;
        }

        public int getEMode()
        {
            return _eMode;
        }

        public string getEModeName()
        {
            return _emodeLabels[_eMode];
        }

        public void setEMode(int m)
        {
            if (m > EMODE_SHIFT) m = EMODE_OWERWRITE;
            _eMode = m;
        }

        public int toggleEditMode()
        {
            setEMode(_eMode + 1);
            return _eMode;
        } 
 
        public string[] getPreviousLines( int n)
        {
            List<string> tmp = new List<string>();
            tmp.Add(getCurrentLine());
            if( _counter == 0) return tmp.ToArray();
            uint tmpCtr = _counter;
            while( tmp.Count<n)
            {
                decrementCounter();
                tmp.Add(getCurrentLine());
                if (_counter == 0) break;
            }
            setCounter(tmpCtr);
            return tmp.ToArray();
        }

        public bool isAtStop()
        {
            return UniversalValue._identicalTo_P( getCurrentLine(), "STOP");
        }

        //public const int ProgramSize = 1000;

        //private MK52_Host _parent = null;
        //private Dictionary<int, string> ProgramMemory = new Dictionary<int, string>();

        //public RPN_Counter Counter = new RPN_Counter( "PC", ProgramSize);
        //public InputReceiver_String Text = null;
        //public InputReceiver_Value Number = null;

        //public Program_Memory( MK52_Host parent)
        //{
        //    _parent = parent;
        //    Text = new InputReceiver_String(parent);
        //    Number = new InputReceiver_Value( parent);
        //}

        //public void Clear()
        //{
        //    ProgramMemory.Clear();
        //    Counter.Set(0);
        //}

        //public bool isAtStop
        //{
        //    get
        //    {
        //        return GetCurrentLine().Trim().StartsWith("STOP");
        //    }
        //}
        
        //public string GetCurrentLine()
        //{
        //    return GetLine( Counter.V);
        //}

        //public void SetCurrentLine( string line)
        //{
        //    SetLine(Counter.V, line);
        //}

        //public void AppendCurrentLine(string line)
        //{
        //    string tmp = GetCurrentLine();
        //    SetCurrentLine( tmp + line);
        //}

        //public void AppendCounterString()
        //{
        //    string tmp = GetCurrentLine();
        //    if( tmp.Length <= 0) return;
        //    SetCurrentLine(tmp + Counter.entryResult.ToString("000"));
        //}

        //public void ExecuteCurrentLine()
        //{
        //    string line = GetCurrentLine().Trim();
        //    //if (_parent.Functions["Empty"].execute(_parent, line)) return;
        //    //if (_parent.Functions["Comment"].execute(_parent, line)) return;
        //    //if (_parent.Functions["STOP"].execute(_parent, line)) return;
        //    if (_parent.Functions.ContainsKey(line))
        //    {
        //        RPN_Function f = _parent.Functions[line];
        //        f.execute(_parent, line);
        //        Counter.Increment();
        //        return;
        //    }
        //    foreach (string k in _parent.Functions.Keys)
        //    {
        //        //if( _parent.Functions[k].execute(_parent,  line))
        //            return;
        //    }
        //    //_parent.CalcStack.X_Label = "Not Found: " + line;
        //    Counter.Increment();
        //}

        //public string GetLine( int number)
        //{
        //    if( !ProgramMemory.ContainsKey( number)) return ""; // string empty
        //    return ProgramMemory[number];
        //}

        //public void SetLine( int number, string line)
        //{
        //    if (line.Length == 0)
        //    {
        //        if( ProgramMemory.ContainsKey(number))
        //            ProgramMemory.Remove(number);
        //        return;
        //    }
        //    if (!ProgramMemory.ContainsKey(number))
        //    {
        //        ProgramMemory.Add(number, line);
        //        return;
        //    }
        //    ProgramMemory[number] = line;
        //}

        //public void InsertLine(int number, string line)
        //{
        //    //for( i

        //    if (line.Length == 0)
        //    {
        //        if (ProgramMemory.ContainsKey(number))
        //            ProgramMemory.Remove(number);
        //        return;
        //    }
        //    if (!ProgramMemory.ContainsKey(number))
        //    {
        //        ProgramMemory.Add(number, line);
        //        return;
        //    }
        //    ProgramMemory[number] = line;
        //}

        //public bool LoadLine(string s)
        //{
        //    if (!s.StartsWith("P")) return false;
        //    if (PCLoadHelper(s)) return true;
        //    int number = Convert.ToInt32(s.Substring(1, 3));
        //    SetLine( number, s.Substring(5).Trim());
        //    return true;
        //}

        //public bool Load(StreamReader sr)
        //{
        //    ProgramMemory.Clear();
        //    while( !sr.EndOfStream)
        //    {
        //        string s = sr.ReadLine().Trim();
        //        if( s.Length == 0 || s.StartsWith("#")) continue;
        //        LoadLine(s);
        //    }
        //    return true;
        //}

        //private bool PCLoadHelper(string s)
        //{
        //    if (!s.StartsWith("PC = ")) return false;
        //    Counter.Set(Convert.ToInt32(s.Substring(5).Trim()));
        //    return true;
        //}

        //public void Save(StreamWriter sw)
        //{
        //    sw.Write("#\n");
        //    sw.Write("# Program:\n");
        //    sw.Write("#\n");
        //    sw.Write("PC = " + Counter.V.ToString() + "\n");
        //    for( int k=0; k<Counter.MaxValue; k++)
        //    {
        //        if (!ProgramMemory.ContainsKey(k)) continue;
        //        string v = ProgramMemory[k];
        //        if (v.Length == 0) continue;
        //        sw.Write(k.ToString("P000: ") + v + "\n");
        //    }
        //}
    }
}
