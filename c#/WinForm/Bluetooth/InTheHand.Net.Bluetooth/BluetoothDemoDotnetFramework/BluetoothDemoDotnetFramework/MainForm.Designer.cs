
namespace BluetoothDemoDotnetFramework
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.mainToolStrip_ = new System.Windows.Forms.ToolStrip();
            this.devicesToolStripComboBox_ = new System.Windows.Forms.ToolStripComboBox();
            this.mainStatusStrip_ = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel_ = new System.Windows.Forms.ToolStripStatusLabel();
            this.refreshToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.spinningCircles_ = new BluetoothDemoDotnetFramework.SpinningCircles();
            this.connectToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.mainToolStrip_.SuspendLayout();
            this.mainStatusStrip_.SuspendLayout();
            this.SuspendLayout();
            // 
            // mainToolStrip_
            // 
            this.mainToolStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.devicesToolStripComboBox_,
            this.refreshToolStripButton_,
            this.connectToolStripButton_});
            this.mainToolStrip_.Location = new System.Drawing.Point(0, 0);
            this.mainToolStrip_.Name = "mainToolStrip_";
            this.mainToolStrip_.Size = new System.Drawing.Size(800, 25);
            this.mainToolStrip_.TabIndex = 0;
            this.mainToolStrip_.Text = "toolStrip1";
            // 
            // devicesToolStripComboBox_
            // 
            this.devicesToolStripComboBox_.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.devicesToolStripComboBox_.Name = "devicesToolStripComboBox_";
            this.devicesToolStripComboBox_.Size = new System.Drawing.Size(160, 25);
            this.devicesToolStripComboBox_.SelectedIndexChanged += new System.EventHandler(this.devicesToolStripComboBox__SelectedIndexChanged);
            // 
            // mainStatusStrip_
            // 
            this.mainStatusStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel_});
            this.mainStatusStrip_.Location = new System.Drawing.Point(0, 428);
            this.mainStatusStrip_.Name = "mainStatusStrip_";
            this.mainStatusStrip_.Size = new System.Drawing.Size(800, 22);
            this.mainStatusStrip_.TabIndex = 1;
            // 
            // toolStripStatusLabel_
            // 
            this.toolStripStatusLabel_.Name = "toolStripStatusLabel_";
            this.toolStripStatusLabel_.Size = new System.Drawing.Size(23, 17);
            this.toolStripStatusLabel_.Text = "---";
            // 
            // refreshToolStripButton_
            // 
            this.refreshToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.refreshToolStripButton_.Image = ((System.Drawing.Image)(resources.GetObject("refreshToolStripButton_.Image")));
            this.refreshToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.refreshToolStripButton_.Name = "refreshToolStripButton_";
            this.refreshToolStripButton_.Size = new System.Drawing.Size(56, 22);
            this.refreshToolStripButton_.Text = "Refresh";
            this.refreshToolStripButton_.Click += new System.EventHandler(this.refreshToolStripButton__Click);
            // 
            // spinningCircles_
            // 
            this.spinningCircles_.BackColor = System.Drawing.Color.Transparent;
            this.spinningCircles_.Location = new System.Drawing.Point(418, 168);
            this.spinningCircles_.Name = "spinningCircles_";
            this.spinningCircles_.Size = new System.Drawing.Size(100, 100);
            this.spinningCircles_.TabIndex = 2;
            this.spinningCircles_.Visible = false;
            // 
            // connectToolStripButton_
            // 
            this.connectToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.connectToolStripButton_.Enabled = false;
            this.connectToolStripButton_.Image = ((System.Drawing.Image)(resources.GetObject("connectToolStripButton_.Image")));
            this.connectToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.connectToolStripButton_.Name = "connectToolStripButton_";
            this.connectToolStripButton_.Size = new System.Drawing.Size(59, 22);
            this.connectToolStripButton_.Text = "Connect";
            this.connectToolStripButton_.Click += new System.EventHandler(this.connectToolStripButton__Click);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.spinningCircles_);
            this.Controls.Add(this.mainStatusStrip_);
            this.Controls.Add(this.mainToolStrip_);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Bluetooth Demo";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.Layout += new System.Windows.Forms.LayoutEventHandler(this.MainForm_Layout);
            this.mainToolStrip_.ResumeLayout(false);
            this.mainToolStrip_.PerformLayout();
            this.mainStatusStrip_.ResumeLayout(false);
            this.mainStatusStrip_.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip mainToolStrip_;
        private System.Windows.Forms.ToolStripComboBox devicesToolStripComboBox_;
        private System.Windows.Forms.StatusStrip mainStatusStrip_;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_;
        private System.Windows.Forms.ToolStripButton refreshToolStripButton_;
        private SpinningCircles spinningCircles_;
        private System.Windows.Forms.ToolStripButton connectToolStripButton_;
    }
}

