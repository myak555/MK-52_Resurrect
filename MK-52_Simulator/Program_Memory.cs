using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class Program_Memory
    {
        private uint _counter = 0;
        private Dictionary<int, string> _lines = new Dictionary<int,string>();

        //public void init();
        //public void clear();
        //public void resetCounter();

        public uint getCounter()
        {
            return _counter;
        }

        //public uint setCounter(uint c);
        //public bool incrementCounter();
        //public bool decrementCounter();

        public uint free()
        {
            return 64000;
        }

        public string getCurrentLine()
        {
            return "";
        }

        public string getNextLine()
        {
            return "";
        }

        //public bool appendLine(string line);
        //public bool replaceLine(string line);
        //public bool insertLine(string line);
        //public void deleteLine();
    }
}
