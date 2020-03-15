namespace BaiduBOSDemo
{
    partial class BaiduBOSForm
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(BaiduBOSForm));
            this.filePathTextBox_ = new System.Windows.Forms.TextBox();
            this.uploadButton_ = new System.Windows.Forms.Button();
            this.transmissionProgressBar_ = new System.Windows.Forms.ProgressBar();
            this.selectFileButton_ = new System.Windows.Forms.Button();
            this.toolStrip1 = new System.Windows.Forms.ToolStrip();
            this.settingsToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.bucketTabControl_ = new Common.WinForms.TabControlEx();
            this.toolStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // filePathTextBox_
            // 
            this.filePathTextBox_.Location = new System.Drawing.Point(14, 511);
            this.filePathTextBox_.Name = "filePathTextBox_";
            this.filePathTextBox_.Size = new System.Drawing.Size(531, 21);
            this.filePathTextBox_.TabIndex = 2;
            // 
            // uploadButton_
            // 
            this.uploadButton_.Location = new System.Drawing.Point(551, 539);
            this.uploadButton_.Name = "uploadButton_";
            this.uploadButton_.Size = new System.Drawing.Size(226, 23);
            this.uploadButton_.TabIndex = 3;
            this.uploadButton_.Text = "Upload";
            this.uploadButton_.UseVisualStyleBackColor = true;
            this.uploadButton_.Click += new System.EventHandler(this.uploadButton_Click);
            // 
            // transmissionProgressBar_
            // 
            this.transmissionProgressBar_.Location = new System.Drawing.Point(14, 539);
            this.transmissionProgressBar_.Name = "transmissionProgressBar_";
            this.transmissionProgressBar_.Size = new System.Drawing.Size(531, 23);
            this.transmissionProgressBar_.TabIndex = 4;
            // 
            // selectFileButton_
            // 
            this.selectFileButton_.Location = new System.Drawing.Point(551, 510);
            this.selectFileButton_.Name = "selectFileButton_";
            this.selectFileButton_.Size = new System.Drawing.Size(226, 23);
            this.selectFileButton_.TabIndex = 8;
            this.selectFileButton_.Text = "Select a File";
            this.selectFileButton_.UseVisualStyleBackColor = true;
            this.selectFileButton_.Click += new System.EventHandler(this.selectFileButton_Click);
            // 
            // toolStrip1
            // 
            this.toolStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.settingsToolStripButton_});
            this.toolStrip1.Location = new System.Drawing.Point(20, 60);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new System.Drawing.Size(760, 25);
            this.toolStrip1.TabIndex = 11;
            this.toolStrip1.Text = "toolStrip1";
            // 
            // settingsToolStripButton_
            // 
            this.settingsToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.settingsToolStripButton_.Image = ((System.Drawing.Image)(resources.GetObject("settingsToolStripButton_.Image")));
            this.settingsToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.settingsToolStripButton_.Name = "settingsToolStripButton_";
            this.settingsToolStripButton_.Size = new System.Drawing.Size(58, 22);
            this.settingsToolStripButton_.Text = "Settings";
            this.settingsToolStripButton_.Click += new System.EventHandler(this.settingsToolStripButton__Click);
            // 
            // bucketTabControl_
            // 
            this.bucketTabControl_.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bucketTabControl_.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.bucketTabControl_.Location = new System.Drawing.Point(14, 93);
            this.bucketTabControl_.Name = "bucketTabControl_";
            this.bucketTabControl_.Padding = new System.Drawing.Point(12, 4);
            this.bucketTabControl_.SelectedIndex = 0;
            this.bucketTabControl_.Size = new System.Drawing.Size(774, 265);
            this.bucketTabControl_.TabIndex = 10;
            this.bucketTabControl_.Selected += new System.Windows.Forms.TabControlEventHandler(this.bucketTabControl__Selected);
            // 
            // BaiduBOSForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 638);
            this.Controls.Add(this.toolStrip1);
            this.Controls.Add(this.bucketTabControl_);
            this.Controls.Add(this.selectFileButton_);
            this.Controls.Add(this.transmissionProgressBar_);
            this.Controls.Add(this.uploadButton_);
            this.Controls.Add(this.filePathTextBox_);
            this.Name = "BaiduBOSForm";
            this.Text = "Baidu BOS";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.BaiduBOSForm_FormClosed);
            this.Load += new System.EventHandler(this.BaiduBOSForm_Load);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.TextBox filePathTextBox_;
        private System.Windows.Forms.Button uploadButton_;
        private System.Windows.Forms.ProgressBar transmissionProgressBar_;
        private System.Windows.Forms.Button selectFileButton_;
        private Common.WinForms.TabControlEx bucketTabControl_;
        private System.Windows.Forms.ToolStrip toolStrip1;
        private System.Windows.Forms.ToolStripButton settingsToolStripButton_;
    }
}

