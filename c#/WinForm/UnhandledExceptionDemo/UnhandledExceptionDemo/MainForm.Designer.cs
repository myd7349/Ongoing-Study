
namespace UnhandledExceptionDemo
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
            this.throwUnhandledExceptionButton_ = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // throwUnhandledExceptionButton_
            // 
            this.throwUnhandledExceptionButton_.Location = new System.Drawing.Point(42, 36);
            this.throwUnhandledExceptionButton_.Name = "throwUnhandledExceptionButton_";
            this.throwUnhandledExceptionButton_.Size = new System.Drawing.Size(191, 43);
            this.throwUnhandledExceptionButton_.TabIndex = 0;
            this.throwUnhandledExceptionButton_.Text = "Throw Unhandled Exception";
            this.throwUnhandledExceptionButton_.UseVisualStyleBackColor = true;
            this.throwUnhandledExceptionButton_.Click += new System.EventHandler(this.throwUnhandledExceptionButton__Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(576, 267);
            this.Controls.Add(this.throwUnhandledExceptionButton_);
            this.Name = "MainForm";
            this.Text = "Main Form";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button throwUnhandledExceptionButton_;
    }
}

