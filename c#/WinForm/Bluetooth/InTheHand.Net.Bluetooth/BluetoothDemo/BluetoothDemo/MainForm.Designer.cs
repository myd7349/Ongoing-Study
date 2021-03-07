
namespace BluetoothDemo
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.mainToolStrip_ = new System.Windows.Forms.ToolStrip();
            this.devicesToolStripComboBox_ = new System.Windows.Forms.ToolStripComboBox();
            this.refreshDevicesToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.connectToolStripButton_ = new System.Windows.Forms.ToolStripButton();
            this.mainStatusStrip_ = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel_ = new System.Windows.Forms.ToolStripStatusLabel();
            this.transparentPictureBox_ = new BluetoothDemo.TransparentPictureBox();
            this.mainToolStrip_.SuspendLayout();
            this.mainStatusStrip_.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.transparentPictureBox_)).BeginInit();
            this.SuspendLayout();
            // 
            // mainToolStrip_
            // 
            this.mainToolStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.devicesToolStripComboBox_,
            this.refreshDevicesToolStripButton_,
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
            // refreshDevicesToolStripButton_
            // 
            this.refreshDevicesToolStripButton_.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Text;
            this.refreshDevicesToolStripButton_.Image = ((System.Drawing.Image)(resources.GetObject("refreshDevicesToolStripButton_.Image")));
            this.refreshDevicesToolStripButton_.ImageTransparentColor = System.Drawing.Color.Magenta;
            this.refreshDevicesToolStripButton_.Name = "refreshDevicesToolStripButton_";
            this.refreshDevicesToolStripButton_.Size = new System.Drawing.Size(56, 22);
            this.refreshDevicesToolStripButton_.Text = "Refresh";
            this.refreshDevicesToolStripButton_.Click += new System.EventHandler(this.refreshDevicesToolStripButton__Click);
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
            // mainStatusStrip_
            // 
            this.mainStatusStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel_});
            this.mainStatusStrip_.Location = new System.Drawing.Point(0, 493);
            this.mainStatusStrip_.Name = "mainStatusStrip_";
            this.mainStatusStrip_.Size = new System.Drawing.Size(800, 22);
            this.mainStatusStrip_.TabIndex = 1;
            // 
            // toolStripStatusLabel_
            // 
            this.toolStripStatusLabel_.Name = "toolStripStatusLabel_";
            this.toolStripStatusLabel_.Size = new System.Drawing.Size(0, 17);
            // 
            // transparentPictureBox_
            // 
            this.transparentPictureBox_.BackColor = System.Drawing.Color.Transparent;
            this.transparentPictureBox_.Image = ((System.Drawing.Image)(resources.GetObject("transparentPictureBox_.Image")));
            this.transparentPictureBox_.Location = new System.Drawing.Point(319, 162);
            this.transparentPictureBox_.Name = "transparentPictureBox_";
            this.transparentPictureBox_.Size = new System.Drawing.Size(100, 100);
            this.transparentPictureBox_.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.transparentPictureBox_.TabIndex = 5;
            this.transparentPictureBox_.TabStop = false;
            this.transparentPictureBox_.Visible = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 17F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 515);
            this.Controls.Add(this.transparentPictureBox_);
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
            ((System.ComponentModel.ISupportInitialize)(this.transparentPictureBox_)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ToolStrip mainToolStrip_;
        private System.Windows.Forms.ToolStripComboBox devicesToolStripComboBox_;
        private System.Windows.Forms.ToolStripButton refreshDevicesToolStripButton_;
        private System.Windows.Forms.StatusStrip mainStatusStrip_;
        private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel_;
        private System.Windows.Forms.ToolStripButton connectToolStripButton_;
        private TransparentPictureBox transparentPictureBox_;
    }
}

