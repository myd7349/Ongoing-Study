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
            this.mainToolStrip_ = new System.Windows.Forms.ToolStrip();
            this.uploadToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.downloadToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.deleteToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.refreshToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.propertiesToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.firstToolStripSeparator_ = new System.Windows.Forms.ToolStripSeparator();
            this.settingsToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.secondToolStripSeparator_ = new System.Windows.Forms.ToolStripSeparator();
            this.objectFilterToolStripTextBox_ = new System.Windows.Forms.ToolStripTextBox();
            this.delimiterToolStripTextBox_ = new System.Windows.Forms.ToolStripTextBox();
            this.thirdToolStripSeparator_ = new System.Windows.Forms.ToolStripSeparator();
            this.toolStripProgressBar_ = new System.Windows.Forms.ToolStripProgressBar();
            this.pauseToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.abortToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.bucketTabControl_ = new Common.WinForms.TabControlEx();
            this.statusStrip_ = new System.Windows.Forms.StatusStrip();
            this.totalObjectsToolStripStatusLabel_ = new System.Windows.Forms.ToolStripStatusLabel();
            this.totalObjectsNumbertoolStripStatusLabel_ = new System.Windows.Forms.ToolStripStatusLabel();
            this.mainToolStrip_.SuspendLayout();
            this.statusStrip_.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainToolStrip_
            // 
            this.mainToolStrip_.ImageScalingSize = new System.Drawing.Size(36, 36);
            this.mainToolStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.uploadToolStripButton_,
            this.downloadToolStripButton_,
            this.deleteToolStripButton_,
            this.refreshToolStripButton_,
            this.propertiesToolStripButton_,
            this.firstToolStripSeparator_,
            this.settingsToolStripButton_,
            this.secondToolStripSeparator_,
            this.objectFilterToolStripTextBox_,
            this.delimiterToolStripTextBox_,
            this.thirdToolStripSeparator_,
            this.toolStripProgressBar_,
            this.pauseToolStripButton_,
            this.abortToolStripButton_});
            this.mainToolStrip_.Location = new System.Drawing.Point(20, 60);
            this.mainToolStrip_.Name = "mainToolStrip_";
            this.mainToolStrip_.Size = new System.Drawing.Size(920, 43);
            this.mainToolStrip_.TabIndex = 11;
            this.mainToolStrip_.Text = "toolStrip1";
            // 
            // uploadToolStripButton_
            // 
            this.uploadToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.uploadToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Add;
            this.uploadToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.uploadToolStripButton_.Name = "uploadToolStripButton_";
            this.uploadToolStripButton_.Size = new System.Drawing.Size(40, 40);
            this.uploadToolStripButton_.Text = "Upload";
            this.uploadToolStripButton_.Click += new System.EventHandler(this.uploadToolStripButton__Click);
            // 
            // downloadToolStripButton_
            // 
            this.downloadToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.downloadToolStripButton_.Enabled = false;
            this.downloadToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Download;
            this.downloadToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.downloadToolStripButton_.Name = "downloadToolStripButton_";
            this.downloadToolStripButton_.Size = new System.Drawing.Size(40, 40);
            this.downloadToolStripButton_.Text = "Download";
            this.downloadToolStripButton_.Click += new System.EventHandler(this.downloadToolStripButton__Click);
            // 
            // deleteToolStripButton_
            // 
            this.deleteToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.deleteToolStripButton_.Enabled = false;
            this.deleteToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Delete;
            this.deleteToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.deleteToolStripButton_.Name = "deleteToolStripButton_";
            this.deleteToolStripButton_.Size = new System.Drawing.Size(40, 40);
            this.deleteToolStripButton_.Text = "Delete";
            this.deleteToolStripButton_.Click += new System.EventHandler(this.deleteToolStripButton__Click);
            // 
            // refreshToolStripButton_
            // 
            this.refreshToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.refreshToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Refresh;
            this.refreshToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.refreshToolStripButton_.Name = "refreshToolStripButton_";
            this.refreshToolStripButton_.Size = new System.Drawing.Size(40, 40);
            this.refreshToolStripButton_.Text = "Refresh";
            this.refreshToolStripButton_.Click += new System.EventHandler(this.refreshToolStripButton__Click);
            // 
            // propertiesToolStripButton_
            // 
            this.propertiesToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.propertiesToolStripButton_.Enabled = false;
            this.propertiesToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Properties;
            this.propertiesToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.propertiesToolStripButton_.Name = "propertiesToolStripButton_";
            this.propertiesToolStripButton_.Size = new System.Drawing.Size(40, 40);
            this.propertiesToolStripButton_.Text = "Properties";
            this.propertiesToolStripButton_.Click += new System.EventHandler(this.propertiesToolStripButton__Click);
            // 
            // firstToolStripSeparator_
            // 
            this.firstToolStripSeparator_.Name = "firstToolStripSeparator_";
            this.firstToolStripSeparator_.Size = new System.Drawing.Size(6, 43);
            // 
            // settingsToolStripButton_
            // 
            this.settingsToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.settingsToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Settings;
            this.settingsToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.settingsToolStripButton_.Name = "settingsToolStripButton_";
            this.settingsToolStripButton_.Size = new System.Drawing.Size(40, 40);
            this.settingsToolStripButton_.Text = "Settings";
            this.settingsToolStripButton_.Click += new System.EventHandler(this.settingsToolStripButton__Click);
            // 
            // secondToolStripSeparator_
            // 
            this.secondToolStripSeparator_.Name = "secondToolStripSeparator_";
            this.secondToolStripSeparator_.Size = new System.Drawing.Size(6, 43);
            // 
            // objectFilterToolStripTextBox_
            // 
            this.objectFilterToolStripTextBox_.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F);
            this.objectFilterToolStripTextBox_.Name = "objectFilterToolStripTextBox_";
            this.objectFilterToolStripTextBox_.Size = new System.Drawing.Size(160, 43);
            this.objectFilterToolStripTextBox_.TextChanged += new System.EventHandler(this.objectFilterToolStripTextBox__TextChanged);
            // 
            // delimiterToolStripTextBox_
            // 
            this.delimiterToolStripTextBox_.Font = new System.Drawing.Font("Microsoft YaHei UI", 9F);
            this.delimiterToolStripTextBox_.Name = "delimiterToolStripTextBox_";
            this.delimiterToolStripTextBox_.Size = new System.Drawing.Size(80, 43);
            // 
            // thirdToolStripSeparator_
            // 
            this.thirdToolStripSeparator_.Name = "thirdToolStripSeparator_";
            this.thirdToolStripSeparator_.Size = new System.Drawing.Size(6, 43);
            // 
            // toolStripProgressBar_
            // 
            this.toolStripProgressBar_.AutoSize = false;
            this.toolStripProgressBar_.Name = "toolStripProgressBar_";
            this.toolStripProgressBar_.Size = new System.Drawing.Size(200, 25);
            this.toolStripProgressBar_.Visible = false;
            // 
            // pauseToolStripButton_
            // 
            this.pauseToolStripButton_.AutoSize = false;
            this.pauseToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.pauseToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Pause;
            this.pauseToolStripButton_.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.pauseToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.pauseToolStripButton_.Name = "pauseToolStripButton_";
            this.pauseToolStripButton_.Size = new System.Drawing.Size(26, 26);
            this.pauseToolStripButton_.Text = "Pause";
            this.pauseToolStripButton_.Visible = false;
            this.pauseToolStripButton_.Click += new System.EventHandler(this.pauseToolStripButton__Click);
            // 
            // abortToolStripButton_
            // 
            this.abortToolStripButton_.AutoSize = false;
            this.abortToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.abortToolStripButton_.Image = global::BaiduBOSDemo.Properties.Resources.Cancel;
            this.abortToolStripButton_.ImageAlign = System.Drawing.ContentAlignment.MiddleLeft;
            this.abortToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.abortToolStripButton_.Name = "abortToolStripButton_";
            this.abortToolStripButton_.Size = new System.Drawing.Size(26, 26);
            this.abortToolStripButton_.Text = "Abort";
            this.abortToolStripButton_.Visible = false;
            this.abortToolStripButton_.Click += new System.EventHandler(this.abortToolStripButton__Click);
            // 
            // bucketTabControl_
            // 
            this.bucketTabControl_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bucketTabControl_.DrawMode = System.Windows.Forms.TabDrawMode.OwnerDrawFixed;
            this.bucketTabControl_.Location = new System.Drawing.Point(20, 106);
            this.bucketTabControl_.Name = "bucketTabControl_";
            this.bucketTabControl_.Padding = new System.Drawing.Point(12, 4);
            this.bucketTabControl_.SelectedIndex = 0;
            this.bucketTabControl_.Size = new System.Drawing.Size(920, 569);
            this.bucketTabControl_.TabIndex = 10;
            this.bucketTabControl_.Selected += new System.Windows.Forms.TabControlEventHandler(this.bucketTabControl__Selected);
            // 
            // statusStrip_
            // 
            this.statusStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.totalObjectsToolStripStatusLabel_,
            this.totalObjectsNumbertoolStripStatusLabel_});
            this.statusStrip_.Location = new System.Drawing.Point(20, 678);
            this.statusStrip_.Name = "statusStrip_";
            this.statusStrip_.Size = new System.Drawing.Size(920, 22);
            this.statusStrip_.SizingGrip = false;
            this.statusStrip_.TabIndex = 12;
            // 
            // totalObjectsToolStripStatusLabel_
            // 
            this.totalObjectsToolStripStatusLabel_.Name = "totalObjectsToolStripStatusLabel_";
            this.totalObjectsToolStripStatusLabel_.Size = new System.Drawing.Size(88, 17);
            this.totalObjectsToolStripStatusLabel_.Text = "Total Objects:";
            // 
            // totalObjectsNumbertoolStripStatusLabel_
            // 
            this.totalObjectsNumbertoolStripStatusLabel_.Name = "totalObjectsNumbertoolStripStatusLabel_";
            this.totalObjectsNumbertoolStripStatusLabel_.Size = new System.Drawing.Size(23, 17);
            this.totalObjectsNumbertoolStripStatusLabel_.Text = "---";
            // 
            // BaiduBOSForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(960, 720);
            this.Controls.Add(this.statusStrip_);
            this.Controls.Add(this.mainToolStrip_);
            this.Controls.Add(this.bucketTabControl_);
            this.Name = "BaiduBOSForm";
            this.Text = "Baidu BOS";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.BaiduBOSForm_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.BaiduBOSForm_FormClosed);
            this.Load += new System.EventHandler(this.BaiduBOSForm_Load);
            this.mainToolStrip_.ResumeLayout(false);
            this.mainToolStrip_.PerformLayout();
            this.statusStrip_.ResumeLayout(false);
            this.statusStrip_.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private Common.WinForms.TabControlEx bucketTabControl_;
        private System.Windows.Forms.ToolStrip mainToolStrip_;
        private System.Windows.Forms.ToolStripButton settingsToolStripButton_;
        private System.Windows.Forms.ToolStripButton uploadToolStripButton_;
        private System.Windows.Forms.ToolStripButton downloadToolStripButton_;
        private System.Windows.Forms.ToolStripButton deleteToolStripButton_;
        private System.Windows.Forms.ToolStripSeparator firstToolStripSeparator_;
        private System.Windows.Forms.ToolStripSeparator secondToolStripSeparator_;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar_;
        private System.Windows.Forms.ToolStripButton pauseToolStripButton_;
        private System.Windows.Forms.ToolStripButton abortToolStripButton_;
        private System.Windows.Forms.StatusStrip statusStrip_;
        private System.Windows.Forms.ToolStripStatusLabel totalObjectsToolStripStatusLabel_;
        private System.Windows.Forms.ToolStripStatusLabel totalObjectsNumbertoolStripStatusLabel_;
        private System.Windows.Forms.ToolStripTextBox objectFilterToolStripTextBox_;
        private System.Windows.Forms.ToolStripSeparator thirdToolStripSeparator_;
        private System.Windows.Forms.ToolStripTextBox delimiterToolStripTextBox_;
        private System.Windows.Forms.ToolStripButton propertiesToolStripButton_;
        private System.Windows.Forms.ToolStripButton refreshToolStripButton_;
    }
}

