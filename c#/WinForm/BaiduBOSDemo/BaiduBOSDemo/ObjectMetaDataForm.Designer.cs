namespace BaiduBOSDemo
{
    partial class ObjectMetaDataForm
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
            this.objectPropertyGrid_ = new System.Windows.Forms.PropertyGrid();
            this.urlMetroLabel_ = new MetroFramework.Controls.MetroLabel();
            this.urlMetroTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.generateUrlMetroButton_ = new MetroFramework.Controls.MetroButton();
            this.expiredMetroLabel_ = new MetroFramework.Controls.MetroLabel();
            this.expirationInSecondsMetroTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.secondsMetroLabel_ = new MetroFramework.Controls.MetroLabel();
            this.SuspendLayout();
            // 
            // objectPropertyGrid_
            // 
            this.objectPropertyGrid_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.objectPropertyGrid_.HelpVisible = false;
            this.objectPropertyGrid_.Location = new System.Drawing.Point(24, 64);
            this.objectPropertyGrid_.Name = "objectPropertyGrid_";
            this.objectPropertyGrid_.Size = new System.Drawing.Size(475, 279);
            this.objectPropertyGrid_.TabIndex = 0;
            // 
            // urlMetroLabel_
            // 
            this.urlMetroLabel_.AutoSize = true;
            this.urlMetroLabel_.Location = new System.Drawing.Point(23, 346);
            this.urlMetroLabel_.Name = "urlMetroLabel_";
            this.urlMetroLabel_.Size = new System.Drawing.Size(35, 19);
            this.urlMetroLabel_.TabIndex = 1;
            this.urlMetroLabel_.Text = "URL:";
            // 
            // urlMetroTextBox_
            // 
            this.urlMetroTextBox_.Location = new System.Drawing.Point(64, 349);
            this.urlMetroTextBox_.Multiline = true;
            this.urlMetroTextBox_.Name = "urlMetroTextBox_";
            this.urlMetroTextBox_.ReadOnly = true;
            this.urlMetroTextBox_.Size = new System.Drawing.Size(435, 84);
            this.urlMetroTextBox_.TabIndex = 2;
            // 
            // generateUrlMetroButton_
            // 
            this.generateUrlMetroButton_.Location = new System.Drawing.Point(385, 439);
            this.generateUrlMetroButton_.Name = "generateUrlMetroButton_";
            this.generateUrlMetroButton_.Size = new System.Drawing.Size(114, 23);
            this.generateUrlMetroButton_.TabIndex = 3;
            this.generateUrlMetroButton_.Text = "Generate";
            this.generateUrlMetroButton_.Click += new System.EventHandler(this.generateUrlMetroButton__Click);
            // 
            // expiredMetroLabel_
            // 
            this.expiredMetroLabel_.AutoSize = true;
            this.expiredMetroLabel_.Location = new System.Drawing.Point(23, 439);
            this.expiredMetroLabel_.Name = "expiredMetroLabel_";
            this.expiredMetroLabel_.Size = new System.Drawing.Size(88, 19);
            this.expiredMetroLabel_.TabIndex = 4;
            this.expiredMetroLabel_.Text = "Expired after:";
            // 
            // expirationInSecondsMetroTextBox_
            // 
            this.expirationInSecondsMetroTextBox_.Location = new System.Drawing.Point(115, 439);
            this.expirationInSecondsMetroTextBox_.Name = "expirationInSecondsMetroTextBox_";
            this.expirationInSecondsMetroTextBox_.Size = new System.Drawing.Size(75, 23);
            this.expirationInSecondsMetroTextBox_.TabIndex = 5;
            this.expirationInSecondsMetroTextBox_.Text = "1800";
            // 
            // secondsMetroLabel_
            // 
            this.secondsMetroLabel_.AutoSize = true;
            this.secondsMetroLabel_.Location = new System.Drawing.Point(195, 439);
            this.secondsMetroLabel_.Name = "secondsMetroLabel_";
            this.secondsMetroLabel_.Size = new System.Drawing.Size(184, 19);
            this.secondsMetroLabel_.TabIndex = 6;
            this.secondsMetroLabel_.Text = "seconds(-1 means permanent)";
            // 
            // ObjectMetaDataForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(522, 485);
            this.Controls.Add(this.secondsMetroLabel_);
            this.Controls.Add(this.expirationInSecondsMetroTextBox_);
            this.Controls.Add(this.expiredMetroLabel_);
            this.Controls.Add(this.generateUrlMetroButton_);
            this.Controls.Add(this.urlMetroTextBox_);
            this.Controls.Add(this.urlMetroLabel_);
            this.Controls.Add(this.objectPropertyGrid_);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "ObjectMetaDataForm";
            this.Text = "Object Metadata";
            this.Load += new System.EventHandler(this.ObjectMetaDataForm_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PropertyGrid objectPropertyGrid_;
        private MetroFramework.Controls.MetroLabel urlMetroLabel_;
        private MetroFramework.Controls.MetroTextBox urlMetroTextBox_;
        private MetroFramework.Controls.MetroButton generateUrlMetroButton_;
        private MetroFramework.Controls.MetroLabel expiredMetroLabel_;
        private MetroFramework.Controls.MetroTextBox expirationInSecondsMetroTextBox_;
        private MetroFramework.Controls.MetroLabel secondsMetroLabel_;
    }
}
