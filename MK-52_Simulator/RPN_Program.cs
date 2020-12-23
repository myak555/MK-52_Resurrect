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
    public class RPN_Program
    {
        public const int ProgramSize = 1000;

        private RPN_Calculator _parent = null;
        private Dictionary<int, string> ProgramMemory = new Dictionary<int, string>();

        public RPN_Counter Counter = new RPN_Counter( "PC", ProgramSize);

        public RPN_Program( RPN_Calculator parent)
        {
            _parent = parent;
        }

        public bool isAddressEntry
        {
            get
            {
                return Counter.isActive;
            }
        }
        
        public void ActivateEntry()
        {
            Counter.ActivateEntry();
        }

        public void AddDigitToAddress(string text)
        {
            Counter.AddDigitToAddress(text, true);
        }

        public string GetCurrentLine()
        {
            return GetLine( Counter.V);
        }

        public string GetLine( int number)
        {
            if( !ProgramMemory.ContainsKey( number)) return ""; // string empty
            return ProgramMemory[number];
        }

        public void SetLine( int number, string line)
        {
            if (line.Length == 0)
            {
                if( ProgramMemory.ContainsKey(number))
                    ProgramMemory.Remove(number);
                return;
            }
            if (!ProgramMemory.ContainsKey(number))
            {
                ProgramMemory.Add(number, line);
                return;
            }
            ProgramMemory[number] = line;
        }

        public bool LoadLine(string s)
        {
            if (!s.StartsWith("P")) return false;
            if (PCLoadHelper(s)) return true;
            int number = Convert.ToInt32(s.Substring(1, 3));
            SetLine( number, s.Substring(5).Trim());
            return true;
        }

        public bool Load(StreamReader sr)
        {
            ProgramMemory.Clear();
            while( !sr.EndOfStream)
            {
                string s = sr.ReadLine().Trim();
                if( s.Length == 0 || s.StartsWith("#")) continue;
                LoadLine(s);
            }
            return true;
        }

        private bool PCLoadHelper(string s)
        {
            if (!s.StartsWith("PC = ")) return false;
            Counter.Set(Convert.ToInt32(s.Substring(5).Trim()));
            return true;
        }

        public void Save(StreamWriter sw)
        {
            sw.Write("#\n");
            sw.Write("# Program:\n");
            sw.Write("#\n");
            sw.Write("PC = " + Counter.V.ToString() + "\n");
            for( int k=0; k<Counter.MaxValue; k++)
            {
                if (!ProgramMemory.ContainsKey(k)) continue;
                string v = ProgramMemory[k];
                if (v.Length == 0) continue;
                sw.Write(k.ToString("P000: ") + v + "\n");
            }
        }
    }
}
