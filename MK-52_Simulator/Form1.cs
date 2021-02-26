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
            myRPN.init();
            //myRPN.setDisplay("Splash");
            //myRPN.setReceiver("AUTO_N");
            timer1.Enabled = true;
            return;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            myRPN.tick();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            myRPN.shutdown();
        }

        private void loadProgramToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RPN_Functions fn = _stopIfRunning();
            string name = myRPN.getSD().getWindowsFolderName();
            openFileDialog1.InitialDirectory = name;
            openFileDialog1.FileName = "";
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
                fn.loadProgramFile(openFileDialog1.FileName);
            timer1.Enabled = true;
        }

        private void saveProgramToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string name = myRPN.getSD().getWindowsFileName();
            if (name.Length < 1)
                saveProgramAsToolStripMenuItem_Click(sender, e);
            _stopIfRunning().saveProgramFile(name);
            timer1.Enabled = true;
        }

        private void saveProgramAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RPN_Functions fn = _stopIfRunning();
            string name = myRPN.getSD().getWindowsFolderName();
            saveFileDialog1.InitialDirectory = name;
            saveFileDialog1.FileName = "";
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
                fn.saveProgramFile(saveFileDialog1.FileName);
            timer1.Enabled = true;
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            RPN_Functions fn = _stopIfRunning();
            string name = myRPN.getSD().getFolderName();
            openFileDialog2.InitialDirectory = name;
            openFileDialog2.FileName = "";
            if (openFileDialog2.ShowDialog() == DialogResult.OK)
                fn.loadDataFile(openFileDialog2.FileName);
            timer1.Enabled = true;
        }

        private void recordButtonsToolStripMenuItem_Click(object sender, EventArgs e)
        {

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

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
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
    }
}