using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace MK52Simulator
{
    public partial class ScreenControl : UserControl
    {
        private List<TextBox> Boxes = new List<TextBox>(); 

        public ScreenControl()
        {
            InitializeComponent();
            int h = textBox2.Height;
            Boxes.Add(textBox1);
            Boxes.Add(textBox2);
            Boxes.Add(textBox3);
            Boxes.Add(textBox4);
            Boxes.Add(textBox5);
            Boxes.Add(textBox6);
            Boxes.Add(textBox7);
            Boxes.Add(textBox8);
            Boxes.Add(textBox9);
            for (int i = 0, y = 0; i < Boxes.Count; i++, y += h)
                Boxes[i].Top = 3+y;
        }
        public void PlaceText(string text, int row, int col)
        {
            if (row < 0 || row >= Boxes.Count) return; 
            TextBox tb = Boxes[row];
            if (col < 0 || col > 20) return;
            string tmp = tb.Text.Substring( 0, col);
            tmp += text;
            tb.Text = tmp;
        }
    }
}
