
namespace ModelessForm
{
    partial class ModalForm
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
            this.okButton_ = new System.Windows.Forms.Button();
            this.cancelButton_ = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // okButton_
            // 
            this.okButton_.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.okButton_.Location = new System.Drawing.Point(202, 187);
            this.okButton_.Name = "okButton_";
            this.okButton_.Size = new System.Drawing.Size(104, 34);
            this.okButton_.TabIndex = 0;
            this.okButton_.Text = "OK";
            this.okButton_.UseVisualStyleBackColor = true;
            // 
            // cancelButton_
            // 
            this.cancelButton_.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelButton_.Location = new System.Drawing.Point(327, 187);
            this.cancelButton_.Name = "cancelButton_";
            this.cancelButton_.Size = new System.Drawing.Size(104, 34);
            this.cancelButton_.TabIndex = 1;
            this.cancelButton_.Text = "Cancel";
            this.cancelButton_.UseVisualStyleBackColor = true;
            // 
            // ModalForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(459, 233);
            this.Controls.Add(this.cancelButton_);
            this.Controls.Add(this.okButton_);
            this.Name = "ModalForm";
            this.Text = "Modal Form";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button okButton_;
        private System.Windows.Forms.Button cancelButton_;
    }
}