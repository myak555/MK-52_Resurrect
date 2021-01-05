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
        public RPN_Calculator myRPN = new RPN_Calculator();
        public RPN_Display myDisplay = null;
        public string CurrentFile = "";

        private RPN_Button dummyRunButton = new RPN_Button();

        public Form1()
        {
            InitializeComponent();
            myDisplay = new RPN_Display(myRPN, screenControl1);
            myDisplay.Redraw();
            timer1.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            RPN_Button rpb = keyboardControl1.Available()?
                keyboardControl1.GetButton(): dummyRunButton;
            myRPN.ProcessButton(rpb);
            myDisplay.Redraw();
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            myRPN.Shutdown();
        }

        private void loadProgramToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            if (myRPN.CurrentReceiver.Moniker == "AUTO_R")
                myRPN.setReceiver("AUTO_N");
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                CurrentFile = openFileDialog1.FileName;
                myRPN.loadProgram(CurrentFile);
            }
            timer1.Enabled = true;
        }

        private void saveProgramToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if( CurrentFile.Length <= 2)
                saveProgramAsToolStripMenuItem_Click(sender, e);
            timer1.Enabled = false;
            if (myRPN.CurrentReceiver.Moniker == "AUTO_R")
                myRPN.setReceiver("AUTO_N");
            if (CurrentFile.Length > 2)
                myRPN.saveProgram(CurrentFile);
            timer1.Enabled = true;
        }

        private void saveProgramAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            if (myRPN.CurrentReceiver.Moniker == "AUTO_R")
                myRPN.setReceiver("AUTO_N");
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                CurrentFile = saveFileDialog1.FileName;
                myRPN.saveProgram(CurrentFile);
            }
            timer1.Enabled = true;
        }

        private void functionsListToolStripMenuItem_Click(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            if (myRPN.CurrentReceiver.Moniker == "AUTO_R")
                myRPN.setReceiver("AUTO_N");
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
    }
}