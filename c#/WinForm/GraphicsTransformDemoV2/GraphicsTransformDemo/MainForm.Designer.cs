
namespace GraphicsTransformDemo
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
            this.components = new System.ComponentModel.Container();
            this.contextMenuStrip_ = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.showSettingsFormToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.canvas_ = new Canvas();
            this.contextMenuStrip_.SuspendLayout();
            this.SuspendLayout();
            // 
            // contextMenuStrip_
            // 
            this.contextMenuStrip_.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.showSettingsFormToolStripMenuItem});
            this.contextMenuStrip_.Name = "contextMenuStrip_";
            this.contextMenuStrip_.Size = new System.Drawing.Size(201, 26);
            // 
            // showSettingsFormToolStripMenuItem
            // 
            this.showSettingsFormToolStripMenuItem.Name = "showSettingsFormToolStripMenuItem";
            this.showSettingsFormToolStripMenuItem.Size = new System.Drawing.Size(200, 22);
            this.showSettingsFormToolStripMenuItem.Text = "Show Settings Form...";
            this.showSettingsFormToolStripMenuItem.Click += new System.EventHandler(this.showSettingsFormToolStripMenuItem_Click);
            // 
            // canvasPanel_
            // 
            this.canvas_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.canvas_.Location = new System.Drawing.Point(12, 12);
            this.canvas_.Name = "canvasPanel_";
            this.canvas_.Size = new System.Drawing.Size(555, 396);
            this.canvas_.TabIndex = 1;
            this.canvas_.Paint += canvas__Paint;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(579, 420);
            this.ContextMenuStrip = this.contextMenuStrip_;
            this.Controls.Add(this.canvas_);
            this.Font = new System.Drawing.Font("SimSun", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Margin = new System.Windows.Forms.Padding(6, 5, 6, 5);
            this.Name = "MainForm";
            this.Text = "Form";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MainForm_FormClosing);
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.Layout += new System.Windows.Forms.LayoutEventHandler(this.MainForm_Layout);
            this.Resize += new System.EventHandler(this.MainForm_Resize);
            this.contextMenuStrip_.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ContextMenuStrip contextMenuStrip_;
        private System.Windows.Forms.ToolStripMenuItem showSettingsFormToolStripMenuItem;
        private Canvas canvas_;
    }
}

