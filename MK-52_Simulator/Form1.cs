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

        public Form1()
        {
            InitializeComponent();
            drawScreen();
            timer1.Enabled = true;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (!keyboardControl1.Available()) return;
            Button sb = keyboardControl1.GetButton();
            sb.processPress(myRPN);
            drawScreen();
        }

        private void drawScreen()
        {
            myRPN.setScreenValues();
            for (int i = 0; i < myRPN.screenValues.Length; i++)
            {
                screenControl1.PlaceText(myRPN.screenValues[i], i, 0);
            }
        }
    }
}