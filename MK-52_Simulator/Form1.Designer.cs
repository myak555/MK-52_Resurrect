namespace MK52Simulator
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.screenControl1 = new MK52Simulator.ScreenControl();
            this.keyboardControl1 = new MK52Simulator.KeyboardControl();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.SuspendLayout();
            // 
            // screenControl1
            // 
            this.screenControl1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.screenControl1.Location = new System.Drawing.Point(35, 15);
            this.screenControl1.Name = "screenControl1";
            this.screenControl1.Size = new System.Drawing.Size(371, 236);
            this.screenControl1.TabIndex = 1;
            // 
            // keyboardControl1
            // 
            this.keyboardControl1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("keyboardControl1.BackgroundImage")));
            this.keyboardControl1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.keyboardControl1.Location = new System.Drawing.Point(440, 15);
            this.keyboardControl1.Name = "keyboardControl1";
            this.keyboardControl1.Size = new System.Drawing.Size(560, 275);
            this.keyboardControl1.TabIndex = 0;
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // Form1
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(1012, 303);
            this.Controls.Add(this.screenControl1);
            this.Controls.Add(this.keyboardControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "MK-52";
            this.ResumeLayout(false);

        }

        #endregion

        private KeyboardControl keyboardControl1;
        private ScreenControl screenControl1;
        private System.Windows.Forms.Timer timer1;
    }
}

