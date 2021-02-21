//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace MK52Simulator
{
    public partial class KBD_Manager : UserControl
    {
        private List<MK52_Button> m_Buttons = new List<MK52_Button>();
        private Queue<byte> m_ButtonsPressed = new Queue<byte>();
        private bool _recording = false;
        //private int _recordPosition = 0;
        private List<MK52_Button> _record = new List<MK52_Button>();

        public byte lastScan = 0;
        public DateTime lastScanTime = new DateTime(0);
        public bool LEDOn = true;

        public KBD_Manager()
        {
            InitializeComponent();

            // Buttons by columns:

            m_Buttons.Add(new MK52_Button(40,  30, 1, "F"));
            m_Buttons.Add(new MK52_Button(40,  97, 2, "K"));
            m_Buttons.Add(new MK52_Button(40, 160, 3, "A"));
            m_Buttons.Add(new MK52_Button(40, 223, 4, "\u2191\u2193"));

            m_Buttons.Add(new MK52_Button(105, 30, 5, "ØÃ\u2192"));
            m_Buttons.Add(new MK52_Button(105, 97, 6, "ØÃ\u2190"));
            m_Buttons.Add(new MK52_Button(105, 160, 7, "B/O"));
            m_Buttons.Add(new MK52_Button(105, 223, 8, "Ñ/Ï"));

            m_Buttons.Add(new MK52_Button(165, 30, 9, "M\u2192X"));
            m_Buttons.Add(new MK52_Button(165, 97, 10, "X\u2192M"));
            m_Buttons.Add(new MK52_Button(165, 160, 11, "ÁÏ"));
            m_Buttons.Add(new MK52_Button(165, 223, 12, "ÏÏ"));

            m_Buttons.Add(new MK52_Button(230, 30, 13, "7"));
            m_Buttons.Add(new MK52_Button(230, 97, 14, "4"));
            m_Buttons.Add(new MK52_Button(230, 160, 15, "1"));
            m_Buttons.Add(new MK52_Button(230, 223, 16, "0"));

            m_Buttons.Add(new MK52_Button(295, 30, 17, "8"));
            m_Buttons.Add(new MK52_Button(295, 97, 18, "5"));
            m_Buttons.Add(new MK52_Button(295, 160, 19, "2"));
            m_Buttons.Add(new MK52_Button(295, 223, 20, "."));

            m_Buttons.Add(new MK52_Button(360, 30, 21, "9"));
            m_Buttons.Add(new MK52_Button(360, 97, 22, "6"));
            m_Buttons.Add(new MK52_Button(360, 160, 23, "3"));
            m_Buttons.Add(new MK52_Button(360, 223, 24, "/-/"));

            m_Buttons.Add(new MK52_Button(420, 30, 25, "-"));
            m_Buttons.Add(new MK52_Button(420, 97, 26, "+"));
            m_Buttons.Add(new MK52_Button(420, 160, 27, "\u2194"));
            m_Buttons.Add(new MK52_Button(420, 223, 28, "ÂÏ"));

            m_Buttons.Add(new MK52_Button(485, 30, 29, "/"));
            m_Buttons.Add(new MK52_Button(485, 97, 30, "*"));
            m_Buttons.Add(new MK52_Button(485, 160, 31, "Â\u2191"));
            m_Buttons.Add(new MK52_Button(485, 223, 32, "Cx"));
        }

        public void init()
        {
        }

        public byte scan()
        {
            if( m_ButtonsPressed.Count <= 0) return 0;
            lastScan = m_ButtonsPressed.Dequeue();
            lastScanTime = DateTime.Now;
            return lastScan;
        }

        public byte scanImmediate()
        {
            while( m_ButtonsPressed.Count > 1) m_ButtonsPressed.Dequeue();
            return scan();
        }

        private void KeyboardControl_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button != MouseButtons.Left) return;
            foreach (MK52_Button rpb in m_Buttons)
            {
                if (!rpb.isPressed(e.X, e.Y)) continue;
                m_ButtonsPressed.Enqueue((byte)rpb.Scancode);
                return;
            }
        }

        public void StartRecording()
        {
            _record.Clear();
            _recording = true; 
        }

        public void StopRecording()
        {
            _recording = false;
        }

        public bool isRecording
        {
            get
            {
                return _recording;
            }
        }
    }
}
