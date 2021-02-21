using System;
using System.Collections.Generic;
using System.Text;

namespace MK52Simulator
{
    public class RPN_Function
    {
        public string Description = "Unknown empty function";

        public virtual bool checkID( uint id)
        {
            return false;
        }
        
        public virtual bool checkName(string name)
        {
            return false;
        }

        public virtual string Name()
        {
            return "";
        }

        public virtual string IOName()
        {
            return Name();
        }

        public virtual void execute( MK52_Host components)
        {
            execute( components, null);
        }

        public virtual void execute( MK52_Host components, string command)
        {
            return;
        }

        public virtual void advancePC(MK52_Host components)
        {
            Program_Memory pm = components._m_Program_Memory;
            pm.incrementCounter();
            while (!pm.isAtEnd() && pm.getCurrentLine().Length == 0)
                pm.incrementCounter();
        }

        public virtual bool containsPC()
        {
            return false;
        }

        public virtual bool containsMC()
        {
            return false;
        }

        public virtual bool containsRegister()
        {
            return false;
        }

        protected SD_Manager _SDM(MK52_Host components)
        {
            return components._m_Hardware_SD;
        }
            
        protected RPN_Stack _Stack(MK52_Host components)
        {
            return components._m_RPN_Stack;
        }

        protected Register_Memory _RegMem(MK52_Host components)
        {
            return components._m_Register_Memory;
        }

        protected Program_Memory _ProgMem(MK52_Host components)
        {
            return components._m_Program_Memory;
        }

        protected Extended_Memory _ExtMem(MK52_Host components)
        {
            return components._m_Extended_Memory;
        }

        protected RPN_Stack _dealWithClergy1(MK52_Host components)
        {
            RPN_Stack s = _Stack( components);
            if( s.X.isEmpty()) return null;
            if( double.IsNaN(s.X.toReal())) return null;
            return s; // the rest of ariphmetics
        }

        protected RPN_Stack _dealWithClergy2(MK52_Host components)
        {
            RPN_Stack s = _Stack( components);
            if( s.X.isEmpty() || s.Y.isEmpty()) return null;
            double valueX = s.X.toReal();
            double valueY = s.Y.toReal();

            if( double.IsNaN(valueX) && double.IsNaN(valueY)){
                s.pop(2); // remove Y, leave one NaN in X
                return null;
            }
            if( double.IsNaN(valueX)){
                s.pop(1); // remove X, leave Y
                return null;
            }
            if( double.IsNaN(valueY)){
                s.pop(2); // remove Y, leave X
                return null;
            }
            return s; // the rest of ariphmetics
        }

        protected void _executeLoop(MK52_Host components, string command, uint reg)
        {
            UniversalValue loopReg = _RegMem( components)._registerAddress( (int)reg);
            Int64 t = loopReg.toInt();
            if( t > 0)
            {
                loopReg.fromInt(t - 1);
                _ProgMem( components).setCounter(command);
            }
            else{
                _ProgMem( components).incrementCounter();
            }
        }
    }
}
