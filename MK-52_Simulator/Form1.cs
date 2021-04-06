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
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace MK52Simulator
{
    public partial class Form1 : Form
    {
        public MK52_Host myRPN = null;

        private MK52_Button dummyRunButton = new MK52_Button();

        public Form1()
        {
            InitializeComponent();
            myRPN = new MK52_Host(KBD_Manager1, LCD_Manager1);
            myRPN.init( backgroundWorker1);
            timer1.Enabled = true;
            return;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            myRPN.tick();
            string s = KBD_Manager1.getButtonsRecorderMessage();
            if (label1.Text != s)
            {
                label1.Text = s;
                label1.Refresh();
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            myRPN.shutdown();
        }

        private void programLoad_Click(object sender, EventArgs e)
        {
            RPN_Functions fn = _stopIfRunning();
            string name = myRPN.getSD().getWindowsFolderName();
            openFileDialog1.InitialDirectory = name;
            openFileDialog1.FileName = "";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // Simulator - only (helps debugging!)
                FileInfo fi = new FileInfo(openFileDialog1.FileName);
                myRPN.getSD().setFolder_P(fi.DirectoryName);
                fn.loadProgram(fi.FullName);
                myRPN.current_Receiver.tick(0); // needed to redraw!
            }
            timer1.Enabled = true;
        }

        private void programSave_Click(object sender, EventArgs e)
        {
            string name = myRPN.getSD().getWindowsFileName();
            if (!name.EndsWith(".MK52"))
            {
                programSaveAs_Click(sender, e);
                return;
            }
            _stopIfRunning().saveProgram(name);
            timer1.Enabled = true;
        }

        private void programSaveAs_Click(object sender, EventArgs e)
        {
            RPN_Functions fn = _stopIfRunning();
            string name = myRPN.getSD().getWindowsFolderName();
            saveFileDialog1.InitialDirectory = name;
            saveFileDialog1.FileName = "";
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                fn.saveProgram(saveFileDialog1.FileName);
            timer1.Enabled = true;
        }

        private void programExit_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void dataLoad_Click(object sender, EventArgs e)
        {
            RPN_Functions fn = _stopIfRunning();
            string name = myRPN.getSD().getFolderName();
            openFileDialog2.InitialDirectory = name;
            openFileDialog2.FileName = "";
            if (openFileDialog2.ShowDialog() == DialogResult.OK)
                fn.loadData(openFileDialog2.FileName);
            timer1.Enabled = true;
        }

        private void dataSaveAs_Click(object sender, EventArgs e)
        {
            RPN_Functions fn = _stopIfRunning();
            string name = myRPN.getSD().getWindowsFolderName();
            saveFileDialog2.InitialDirectory = name;
            saveFileDialog2.FileName = "";
            if (saveFileDialog2.ShowDialog() == DialogResult.OK)
                fn.saveData(saveFileDialog2.FileName);
            timer1.Enabled = true;
        }

        private void recordButtonsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            KBD_Manager1.StartRecording();
        }

        private void pauseToolStripMenuItem_Click(object sender, EventArgs e)
        {
            KBD_Manager1.PauseRecording();
        }

        private void stopToolStripMenuItem_Click(object sender, EventArgs e)
        {
            KBD_Manager1.StopRecording();
        }

        private void executeButtonsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            KBD_Manager1.PlayRecorded();
        }

        private void loadButtonsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog3.ShowDialog() != DialogResult.OK) return;
            KBD_Manager1.LoadRecord(openFileDialog3.FileName);
        }

        private void saveButtonsStripMenuItem_Click(object sender, EventArgs e)
        {
            if (KBD_Manager1._recordFileName.Length == 0)
            {
                saveButtonsAsToolStripMenuItem_Click(sender, e);
                return;
            }
            KBD_Manager1.SaveRecord();
        }

        private void saveButtonsAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (KBD_Manager1._recordFileName.Length != 0)
                saveFileDialog4.FileName = KBD_Manager1._recordFileName;
            if (saveFileDialog4.ShowDialog() != DialogResult.OK) return;
            KBD_Manager1.SaveRecordAs(saveFileDialog4.FileName);
        }

        private void functionsListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _stopIfRunning();
            if (saveFileDialog3.ShowDialog() == DialogResult.OK)
            {
                myRPN.listFunctions(saveFileDialog3.FileName);
            }
            timer1.Enabled = true;
        }

        private void fontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            _stopIfRunning().requestNextReceiver("FontTest");
        }

        private RPN_Functions _stopIfRunning()
        {
            RPN_Functions fn = myRPN.getFunctions(); 
            timer1.Enabled = false;
            if (myRPN.current_Receiver.Moniker != "AUTO_R") return fn;
            fn.requestNextReceiver("AUTO_N");
            myRPN.tick();
            return fn;
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            RPN_Functions _rpnf = myRPN.getFunctions();
            while (!backgroundWorker1.CancellationPending)
            {
                _rpnf.executeRun();
                if (_rpnf._atStop) break;
            }
        }

        private void backgroundWorker1_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            // TODO: force status update
        }

        private void button_Record_Click(object sender, EventArgs e)
        {
            KBD_Manager1.StartRecording();
        }

        private void button_Pause_Click(object sender, EventArgs e)
        {
            KBD_Manager1.PauseRecording();
        }

        private void button_Stop_Click(object sender, EventArgs e)
        {
            KBD_Manager1.StopRecording();
        }

        private void button_Execute_Click(object sender, EventArgs e)
        {
            KBD_Manager1.PlayRecorded();
        }

        private void backgroundWorker1_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            myRPN.getFunctions().requestNextReceiver("AUTO_N");
            myRPN.setRequestedReceiver();
            myRPN.tick();
        }

        private void button_CopyX_Click(object sender, EventArgs e)
        {
            Clipboard.SetText(myRPN._m_RPN_Stack.X.toString());
        }
    }
}