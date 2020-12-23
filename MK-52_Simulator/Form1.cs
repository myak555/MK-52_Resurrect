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
    }
}