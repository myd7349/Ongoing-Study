
namespace ModelessForm
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
            this.modalButton_ = new System.Windows.Forms.Button();
            this.modelessButton_ = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // modalButton_
            // 
            this.modalButton_.Location = new System.Drawing.Point(12, 13);
            this.modalButton_.Name = "modalButton_";
            this.modalButton_.Size = new System.Drawing.Size(258, 77);
            this.modalButton_.TabIndex = 0;
            this.modalButton_.Text = "Modal";
            this.modalButton_.UseVisualStyleBackColor = true;
            this.modalButton_.Click += new System.EventHandler(this.modalButton__Click);
            // 
            // modelessButton_
            // 
            this.modelessButton_.Location = new System.Drawing.Point(12, 102);
            this.modelessButton_.Name = "modelessButton_";
            this.modelessButton_.Size = new System.Drawing.Size(258, 77);
            this.modelessButton_.TabIndex = 1;
            this.modelessButton_.Text = "Modeless";
            this.modelessButton_.UseVisualStyleBackColor = true;
            this.modelessButton_.Click += new System.EventHandler(this.modelessButton__Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(282, 191);
            this.Controls.Add(this.modelessButton_);
            this.Controls.Add(this.modalButton_);
            this.Name = "MainForm";
            this.Text = "Main Form";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button modalButton_;
        private System.Windows.Forms.Button modelessButton_;
    }
}

