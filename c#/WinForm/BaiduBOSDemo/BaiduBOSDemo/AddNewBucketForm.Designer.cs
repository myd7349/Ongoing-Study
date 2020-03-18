namespace BaiduBOSDemo
{
    partial class AddNewBucketForm
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
            this.bucketNameMetroTextBox_ = new MetroFramework.Controls.MetroTextBox();
            this.okMetroButton_ = new MetroFramework.Controls.MetroButton();
            this.cancelMetroButton_ = new MetroFramework.Controls.MetroButton();
            this.bucketNameMetroLabel_ = new MetroFramework.Controls.MetroLabel();
            this.SuspendLayout();
            // 
            // bucketNameMetroTextBox_
            // 
            this.bucketNameMetroTextBox_.Location = new System.Drawing.Point(13, 99);
            this.bucketNameMetroTextBox_.Name = "bucketNameMetroTextBox_";
            this.bucketNameMetroTextBox_.Size = new System.Drawing.Size(271, 23);
            this.bucketNameMetroTextBox_.TabIndex = 1;
            this.bucketNameMetroTextBox_.TextChanged += new System.EventHandler(this.bucketNameMetroTextBox__TextChanged);
            // 
            // okMetroButton_
            // 
            this.okMetroButton_.DialogResult = System.Windows.Forms.DialogResult.OK;
            this.okMetroButton_.Enabled = false;
            this.okMetroButton_.Location = new System.Drawing.Point(55, 140);
            this.okMetroButton_.Name = "okMetroButton_";
            this.okMetroButton_.Size = new System.Drawing.Size(75, 23);
            this.okMetroButton_.TabIndex = 2;
            this.okMetroButton_.Text = "OK";
            this.okMetroButton_.Click += new System.EventHandler(this.okMetroButton__Click);
            // 
            // cancelMetroButton_
            // 
            this.cancelMetroButton_.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.cancelMetroButton_.Location = new System.Drawing.Point(169, 140);
            this.cancelMetroButton_.Name = "cancelMetroButton_";
            this.cancelMetroButton_.Size = new System.Drawing.Size(75, 23);
            this.cancelMetroButton_.TabIndex = 3;
            this.cancelMetroButton_.Text = "Cancel";
            // 
            // bucketNameMetroLabel_
            // 
            this.bucketNameMetroLabel_.AutoSize = true;
            this.bucketNameMetroLabel_.Location = new System.Drawing.Point(12, 71);
            this.bucketNameMetroLabel_.Name = "bucketNameMetroLabel_";
            this.bucketNameMetroLabel_.Size = new System.Drawing.Size(123, 19);
            this.bucketNameMetroLabel_.TabIndex = 0;
            this.bucketNameMetroLabel_.Text = "Input Bucket Name:";
            // 
            // AddNewBucketForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(299, 177);
            this.Controls.Add(this.cancelMetroButton_);
            this.Controls.Add(this.okMetroButton_);
            this.Controls.Add(this.bucketNameMetroTextBox_);
            this.Controls.Add(this.bucketNameMetroLabel_);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "AddNewBucketForm";
            this.Resizable = false;
            this.Text = "Add New Bucket";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private MetroFramework.Controls.MetroTextBox bucketNameMetroTextBox_;
        private MetroFramework.Controls.MetroButton okMetroButton_;
        private MetroFramework.Controls.MetroButton cancelMetroButton_;
        private MetroFramework.Controls.MetroLabel bucketNameMetroLabel_;
    }
}