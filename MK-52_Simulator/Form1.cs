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
        public string CurrentFile = "";

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
            //if (myRPN.current_Display.Moniker == "Splash")
            //{
            //    myRPN.setDisplay("AUTO");
            //    timer1.Interval = 10;
            //}
            myRPN.tick();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            myRPN.shutdown();
        }

        private void loadProgramToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //timer1.Enabled = false;
            //if (myRPN.current_Receiver.Moniker == "AUTO_R")
            //    myRPN.setReceiver("AUTO_N");
            //openFileDialog1.InitialDirectory = myRPN._m_Hardware_SD.getWindowsFolderName();
            //openFileDialog1.FileName = "";
            //if (openFileDialog1.ShowDialog() == DialogResult.OK)
            //{
            //    CurrentFile = openFileDialog1.FileName;
            //    myRPN.loadProgram(CurrentFile);
            //}
            //timer1.Enabled = true;
        }

        private void saveProgramToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //if( CurrentFile.Length <= 2)
            //    saveProgramAsToolStripMenuItem_Click(sender, e);
            //timer1.Enabled = false;
            //if (myRPN.current_Receiver.Moniker == "AUTO_R")
            //    myRPN.setReceiver("AUTO_N");
            //if (CurrentFile.Length > 2)
            //    myRPN.saveProgram(CurrentFile);
            //timer1.Enabled = true;
        }

        private void saveProgramAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //timer1.Enabled = false;
            //if (myRPN.current_Receiver.Moniker == "AUTO_R")
            //    myRPN.setReceiver("AUTO_N");
            //saveFileDialog1.InitialDirectory = myRPN._m_Hardware_SD.getWindowsFolderName();
            //saveFileDialog1.FileName = "New_Prog.mk52";
            //if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            //{
            //    CurrentFile = saveFileDialog1.FileName;
            //    myRPN.saveProgram(CurrentFile);
            //}
            //timer1.Enabled = true;
        }

        private void recordButtonsToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void functionsListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            //if (myRPN.current_Receiver.Moniker == "AUTO_R")
            //    myRPN.setReceiver("AUTO_N");
            if (saveFileDialog3.ShowDialog() == DialogResult.OK)
            {
                CurrentFile = saveFileDialog3.FileName;
                myRPN.listFunctions(CurrentFile);
            }
            timer1.Enabled = true;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void fontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            myRPN.getFunctions().requestNextReceiver("FontTest");
        }

    }
}