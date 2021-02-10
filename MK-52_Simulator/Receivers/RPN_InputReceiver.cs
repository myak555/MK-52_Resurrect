using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using MK52Simulator;

namespace MK52Simulator.Receivers
{
    //
    // Implements a generic empty receiver
    //
    public class RPN_InputReceiver
    {
        public string Moniker = "";

        protected MK52_Host _parent;
        protected uint _mode = 0;
        protected string _parentReturn = "None";
        protected string _displayName = "   ";
        protected string _inputString = "";

        public RPN_InputReceiver(MK52_Host parent)
        {
            _parent = parent;
        }

        public virtual void activate()
        {
        }

        public virtual void activate( string return_to)
        {
            _parentReturn = return_to;
        }

        public virtual void activate( string return_to, RPN_Button button)
        {
            _parentReturn = return_to;
        }

        public virtual string tick()
        {
            return _parentReturn;
        }

        public virtual string tick( RPN_Button button)
        {
            return _parentReturn;
        }

        public virtual bool isActive
        {
            get
            {
                return _mode != 0;
            }
        }

        public virtual string DisplayName
        {
            get
            {
                return _displayName;
            }
        }
    }
}
