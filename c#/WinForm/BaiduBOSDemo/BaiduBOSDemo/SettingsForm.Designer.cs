namespace BaiduBOSDemo
{
    partial class SettingsForm
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
            this.tableLayoutPanel = new System.Windows.Forms.TableLayoutPanel();
            this.endPointTextBox_ = new System.Windows.Forms.TextBox();
            this.endPointLabel_ = new System.Windows.Forms.Label();
            this.secretAccessKeyTextBox_ = new System.Windows.Forms.TextBox();
            this.accessKeyLabel_ = new System.Windows.Forms.Label();
            this.accessKeyTextBox_ = new System.Windows.Forms.TextBox();
            this.secretAccessKeyLabel_ = new System.Windows.Forms.Label();
            this.tableLayoutPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel
            // 
            this.tableLayoutPanel.ColumnCount = 2;
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle());
            this.tableLayoutPanel.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel.Controls.Add(this.endPointTextBox_, 1, 2);
            this.tableLayoutPanel.Controls.Add(this.endPointLabel_, 0, 2);
            this.tableLayoutPanel.Controls.Add(this.secretAccessKeyTextBox_, 1, 1);
            this.tableLayoutPanel.Controls.Add(this.accessKeyTextBox_, 1, 0);
            this.tableLayoutPanel.Controls.Add(this.secretAccessKeyLabel_, 0, 1);
            this.tableLayoutPanel.Controls.Add(this.accessKeyLabel_, 0, 0);
            this.tableLayoutPanel.Location = new System.Drawing.Point(13, 65);
            this.tableLayoutPanel.Name = "tableLayoutPanel";
            this.tableLayoutPanel.RowCount = 4;
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 20F));
            this.tableLayoutPanel.Size = new System.Drawing.Size(472, 100);
            this.tableLayoutPanel.TabIndex = 0;
            // 
            // endPointTextBox_
            // 
            this.endPointTextBox_.Location = new System.Drawing.Point(122, 63);
            this.endPointTextBox_.Name = "endPointTextBox_";
            this.endPointTextBox_.Size = new System.Drawing.Size(347, 21);
            this.endPointTextBox_.TabIndex = 4;
            // 
            // endPointLabel_
            // 
            this.endPointLabel_.AutoSize = true;
            this.endPointLabel_.Location = new System.Drawing.Point(3, 60);
            this.endPointLabel_.Name = "endPointLabel_";
            this.endPointLabel_.Size = new System.Drawing.Size(65, 12);
            this.endPointLabel_.TabIndex = 3;
            this.endPointLabel_.Text = "End Point:";
            // 
            // secretAccessKeyTextBox_
            // 
            this.secretAccessKeyTextBox_.Location = new System.Drawing.Point(122, 33);
            this.secretAccessKeyTextBox_.Name = "secretAccessKeyTextBox_";
            this.secretAccessKeyTextBox_.Size = new System.Drawing.Size(347, 21);
            this.secretAccessKeyTextBox_.TabIndex = 3;
            // 
            // accessKeyLabel_
            // 
            this.accessKeyLabel_.AutoSize = true;
            this.accessKeyLabel_.Location = new System.Drawing.Point(3, 0);
            this.accessKeyLabel_.Name = "accessKeyLabel_";
            this.accessKeyLabel_.Size = new System.Drawing.Size(71, 12);
            this.accessKeyLabel_.TabIndex = 0;
            this.accessKeyLabel_.Text = "Access Key:";
            // 
            // accessKeyTextBox_
            // 
            this.accessKeyTextBox_.Location = new System.Drawing.Point(122, 3);
            this.accessKeyTextBox_.Name = "accessKeyTextBox_";
            this.accessKeyTextBox_.Size = new System.Drawing.Size(347, 21);
            this.accessKeyTextBox_.TabIndex = 1;
            // 
            // secretAccessKeyLabel_
            // 
            this.secretAccessKeyLabel_.AutoSize = true;
            this.secretAccessKeyLabel_.Location = new System.Drawing.Point(3, 30);
            this.secretAccessKeyLabel_.Name = "secretAccessKeyLabel_";
            this.secretAccessKeyLabel_.Size = new System.Drawing.Size(113, 12);
            this.secretAccessKeyLabel_.TabIndex = 2;
            this.secretAccessKeyLabel_.Text = "Secret Access Key:";
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(500, 190);
            this.Controls.Add(this.tableLayoutPanel);
            this.Name = "SettingsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Settings";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.SettingsForm_FormClosed);
            this.Load += new System.EventHandler(this.SettingsForm_Load);
            this.tableLayoutPanel.ResumeLayout(false);
            this.tableLayoutPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel;
        private System.Windows.Forms.TextBox endPointTextBox_;
        private System.Windows.Forms.Label endPointLabel_;
        private System.Windows.Forms.TextBox secretAccessKeyTextBox_;
        private System.Windows.Forms.Label accessKeyLabel_;
        private System.Windows.Forms.TextBox accessKeyTextBox_;
        private System.Windows.Forms.Label secretAccessKeyLabel_;
    }
}