
namespace ButtonWithoutFocus
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
            this.retryButton_ = new System.Windows.Forms.Button();
            this.retryNoFocusButton_ = new ButtonWithoutFocus.NoFocusButton();
            this.SuspendLayout();
            // 
            // retryButton_
            // 
            this.retryButton_.Location = new System.Drawing.Point(61, 47);
            this.retryButton_.Name = "retryButton_";
            this.retryButton_.Size = new System.Drawing.Size(162, 47);
            this.retryButton_.TabIndex = 1;
            this.retryButton_.Text = "Retry";
            this.retryButton_.UseVisualStyleBackColor = true;
            this.retryButton_.Click += new System.EventHandler(this.retryButton__Click);
            // 
            // retryNoFocusButton_
            // 
            this.retryNoFocusButton_.Location = new System.Drawing.Point(61, 124);
            this.retryNoFocusButton_.Name = "retryNoFocusButton_";
            this.retryNoFocusButton_.Size = new System.Drawing.Size(162, 47);
            this.retryNoFocusButton_.TabIndex = 0;
            this.retryNoFocusButton_.Text = "Retry (No Focus)";
            this.retryNoFocusButton_.UseVisualStyleBackColor = true;
            this.retryNoFocusButton_.Click += new System.EventHandler(this.retryNoFocusButton__Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(637, 340);
            this.Controls.Add(this.retryButton_);
            this.Controls.Add(this.retryNoFocusButton_);
            this.Name = "MainForm";
            this.Text = "Main Form";
            this.ResumeLayout(false);

        }

        #endregion

        private NoFocusButton retryNoFocusButton_;
        private System.Windows.Forms.Button retryButton_;
    }
}

