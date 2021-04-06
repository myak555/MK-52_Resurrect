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
using System.IO;
using System.Windows.Forms;

namespace MK52Simulator
{
    public partial class KBD_Manager : UserControl
    {
        public const int MacroStatus_OFF = 0;
        public const int MacroStatus_RECORDING = 1;
        public const int MacroStatus_PAUSED = 2;
        public const int MacroStatus_PLAYING = 3;
        public int MaxMacro = 1000;

        private List<MK52_Button> m_Buttons = new List<MK52_Button>();
        private Queue<byte> m_ButtonsPressed = new Queue<byte>();
        private int _recording = MacroStatus_OFF;
        private List<byte> _record = new List<byte>();
        public string _recordFileName = "";

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
                byte b = (byte)rpb.Scancode;
                m_ButtonsPressed.Enqueue(b);
                if (_recording == MacroStatus_RECORDING && _record.Count < MaxMacro)
                    _record.Add(b);
                return;
            }
        }

        public void StartRecording()
        {
            _record.Clear();
            _recording = MacroStatus_RECORDING; 
        }

        public void PauseRecording()
        {
            _recording = MacroStatus_PAUSED;
        }

        public void StopRecording()
        {
            _recording = MacroStatus_OFF;
        }

        public void PlayRecorded()
        {
            if (isRecording) return;
            _recording = MacroStatus_PLAYING;
            foreach (byte b in _record)
            {
                m_ButtonsPressed.Enqueue(b);
            }
            _recording = MacroStatus_OFF;
        }

        public void LoadRecord(string filename)
        {
            _recordFileName = filename;
            FileStream fs = null;
            StreamReader sr = null;
            try
            {
                fs = File.Open(_recordFileName, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                sr = new StreamReader(fs);
                _record.Clear();
                while( !sr.EndOfStream)
                {
                    string buttonName = sr.ReadLine();
                    MK52_Button iB = m_Buttons.Find(
                        delegate(MK52_Button x) { return x.Moniker == buttonName;});
                    _record.Add((byte)iB.Scancode);
                }
            }
            catch (Exception ex)
            {
                throw new FileNotFoundException(ex.Message);
            }
            finally
            {
                if (sr != null) sr.Close();
                if (fs != null) fs.Close();
            }
        }

        public void SaveRecord()
        {
            FileStream fs = null;
            StreamWriter sw = null;
            try
            {
                fs = File.Open(_recordFileName, FileMode.Create, FileAccess.Write, FileShare.Read);
                sw = new StreamWriter(fs);
                foreach (byte b in _record)
                {
                    MK52_Button btn = m_Buttons[ (int)b - 1];
                    sw.WriteLine( btn.Moniker);
                }
            }
            catch (Exception ex)
            {
                throw new FileNotFoundException(ex.Message);
            }
            finally
            {
                if (sw != null) sw.Close();
                if (fs != null) fs.Close();
            }
        }

        public void SaveRecordAs(string filename)
        {
            _recordFileName = filename;
            SaveRecord();
        }

        public bool isRecording
        {
            get
            {
                return _recording != MacroStatus_OFF;
            }
        }

        public int ButtonsRecorded
        {
            get
            {
                return _record.Count;
            }
        }

        public string getButtonsRecorderMessage()
        {
            StringBuilder sb = new StringBuilder();
            switch( _recording)
            {
                case MacroStatus_OFF:
                    if( _record.Count == 0) break;
                    sb.Append("Buttons recorded: ");
                    sb.Append( _record.Count.ToString());
                    break;
                case MacroStatus_RECORDING:
                    sb.Append("Recording: ");
                    sb.Append( _record.Count.ToString());
                    break;
                case MacroStatus_PAUSED:
                    sb.Append("Paused: ");
                    sb.Append( _record.Count.ToString());
                    break;
                default:
                    break;
            }
            return sb.ToString();
        }
    }
}
