
namespace TransparentFormDemo
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.exitButton_ = new System.Windows.Forms.Button();
            this.spinningCircles1 = new TransparentFormDemo.SpinningCircles();
            this.SuspendLayout();
            // 
            // exitButton_
            // 
            this.exitButton_.Location = new System.Drawing.Point(12, 185);
            this.exitButton_.Name = "exitButton_";
            this.exitButton_.Size = new System.Drawing.Size(164, 41);
            this.exitButton_.TabIndex = 0;
            this.exitButton_.Text = "Exit";
            this.exitButton_.UseVisualStyleBackColor = true;
            this.exitButton_.Click += new System.EventHandler(this.exitButton__Click);
            // 
            // spinningCircles1
            // 
            this.spinningCircles1.BackColor = System.Drawing.Color.Transparent;
            this.spinningCircles1.Location = new System.Drawing.Point(12, 12);
            this.spinningCircles1.Name = "spinningCircles1";
            this.spinningCircles1.Size = new System.Drawing.Size(164, 157);
            this.spinningCircles1.TabIndex = 1;
            this.spinningCircles1.Text = "spinningCircles1";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.SkyBlue;
            this.ClientSize = new System.Drawing.Size(191, 240);
            this.Controls.Add(this.spinningCircles1);
            this.Controls.Add(this.exitButton_);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Main Form";
            this.TransparencyKey = System.Drawing.Color.SkyBlue;
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button exitButton_;
        private SpinningCircles spinningCircles1;
    }
}

