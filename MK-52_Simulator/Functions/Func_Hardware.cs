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
using System.Threading;

namespace MK52Simulator
{
    public class Func_Delay : RPN_Function
    {
        public Func_Delay()
        {
            Description = "Delay in ms";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_DELAY;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "DELAY ";
        }

        public override void execute(MK52_Host components, string command)
        {
            Thread.Sleep(Convert.ToInt32(command));
        }
    }

    public class Func_LEDOn : RPN_Function
    {
        public Func_LEDOn()
        {
            Description = "Keyboard LED on";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LEDON;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "LED ON";
        }

        public override void execute(MK52_Host components, string command)
        {
            components._m_Hardware_KBD.LEDOn = true;
        }
    }

    public class Func_LEDOff : RPN_Function
    {
        public Func_LEDOff()
        {
            Description = "Keyboard LED off";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LEDOFF;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "LED OFF";
        }

        public override void execute(MK52_Host components, string command)
        {
            components._m_Hardware_KBD.LEDOn = false;
        }
    }

    public class Func_Update : RPN_Function
    {
        public Func_Update()
        {
            Description = "Updates entire LCD (while running)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_UPDATE;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._identicalTo_P(name, Name());
        }

        public override string Name()
        {
            return "UPDATE";
        }

        public override void execute(MK52_Host components, string command)
        {
            RPN_Functions _rpnf = components._m_RPN_Functions;
            LCD_Manager _lcd = components._m_Hardware_LCD;
            RPN_Stack _st = components._m_RPN_Stack;
            Program_Memory _pm = components._m_Program_Memory;
            Extended_Memory _em = components._m_Extended_Memory;
            //_lcd.updateStatus(_pm.getCounter(), _em.getCounter(), _st.getDModeName(), "RUN");
            //_lcd.updateCalcRegister(0, _st.X.toString());
            //_lcd.updateCalcLabel(0, _st.X_Label);
            //_lcd.updateCalcRegister(1, _st.Y.toString());
            //_lcd.updateCalcLabel(1, _st.Y_Label);
            //_lcd.updateCalcRegister(2, _st.Z.toString());
            //_lcd.updateCalcLabel(2, _st.Z_Label);
            //_lcd.updateCalcRegister(3, _st.T.toString());
            //_lcd.updateCalcLabel(3, _st.T_Label);
            //_lcd.requestUpdate();
        }
    }
}
