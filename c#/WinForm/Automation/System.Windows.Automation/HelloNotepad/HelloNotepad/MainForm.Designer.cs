
namespace HelloNotepad
{
    partial class MainForm
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
            this.button_ = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // button_
            // 
            this.button_.Location = new System.Drawing.Point(262, 108);
            this.button_.Name = "button_";
            this.button_.Size = new System.Drawing.Size(124, 36);
            this.button_.TabIndex = 0;
            this.button_.Text = "Hello, Notepad!";
            this.button_.UseVisualStyleBackColor = true;
            this.button_.Click += new System.EventHandler(this.button__Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button_);
            this.Name = "MainForm";
            this.Text = "Main Form";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button_;
    }
}

