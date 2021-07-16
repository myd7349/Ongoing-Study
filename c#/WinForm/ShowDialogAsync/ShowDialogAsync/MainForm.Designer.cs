
namespace ShowDialogAsync
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
            this.loadDataButton_ = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // loadDataButton_
            // 
            this.loadDataButton_.Location = new System.Drawing.Point(32, 26);
            this.loadDataButton_.Name = "loadDataButton_";
            this.loadDataButton_.Size = new System.Drawing.Size(131, 37);
            this.loadDataButton_.TabIndex = 0;
            this.loadDataButton_.Text = "Load Data";
            this.loadDataButton_.UseVisualStyleBackColor = true;
            this.loadDataButton_.Click += new System.EventHandler(this.loadDataButton__Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.loadDataButton_);
            this.Name = "MainForm";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button loadDataButton_;
    }
}

