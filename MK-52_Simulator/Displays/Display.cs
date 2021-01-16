using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator.Displays
{
    //
    // Implements the generic interface to calculator display
    //
    public class Display
    {
        public string Moniker = "Undefined";
        protected MK52_Host _parent = null;
        protected string[] dModeLabels = { "DEG", "RAD", "GRD" };
        protected uint _mode = 0;

        public Display(MK52_Host parent)
        {
            _parent = parent;
        }

        public virtual string activate()
        {
            return "Unchanged";
        }

        public virtual void tick()
        {
        }

        public bool isActive
        {
            get { return _mode != 0;}
        }

        protected void _outputGenericStatus()
        {
            uint pc = Convert.ToUInt32(_parent.Program.Counter.V);
            uint mc = Convert.ToUInt32(_parent.Memory.Counter.V);
            _parent.LCD.outputStatus(pc, mc, dModeLabels[_parent.dMode], _parent.current_Receiver.DisplayName);
        }

        protected void _updateGenericStatus()
        {
            uint pc = Convert.ToUInt32(_parent.Program.Counter.V);
            uint mc = Convert.ToUInt32(_parent.Memory.Counter.V);
            _parent.LCD.updateStatus(pc, mc, dModeLabels[_parent.dMode], _parent.current_Receiver.DisplayName);
        }
    }
 }
