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
    // Implements a generic empty receiver
    //
    public class Receiver
    {
        public string Moniker = "Undefined";

        protected MK52_Host _parent;
        protected uint _mode = 0;
        protected string _return_to = "";
        protected StringBuilder _text = new StringBuilder();
        protected UniversalValue _uv = new UniversalValue();

        public Receiver(MK52_Host parent)
        {
            _parent = parent;
        }

        public virtual void activate( string prevReceiver)
        {
            this._return_to = prevReceiver;
        }

        public virtual byte tick( byte scancode)
        {
            return (byte)0;
        }

        public virtual string toString()
        {
            return _text.ToString();
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append("Receiver [");
            sb.Append(Moniker);
            sb.Append("]: ");
            sb.Append(_text.ToString());
            return sb.ToString();
        }

        public virtual string toTrimmedString()
        {
            return _text.ToString().TrimStart();
        }

        public string getReturnReceiverMoniker()
        {
            if (_return_to.Length <= 0) return "AUTO_N"; // as minimum need to return to AUTO_N
            return _return_to;
        }

        protected char _convertButton( string list, uint scancode)
        {
            if (scancode >= list.Length) return (char)0;
            char c = list[(int)scancode];
            if( c == '#') return (char)0;
            return c;
        }
    }
}
