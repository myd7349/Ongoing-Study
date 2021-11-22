
namespace MetafileViewer
{
    partial class MetafileViewerForm
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
            this.openButton_ = new System.Windows.Forms.Button();
            this.pictureBox_ = new System.Windows.Forms.PictureBox();
            this.propertiesButton_ = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_)).BeginInit();
            this.SuspendLayout();
            // 
            // openButton_
            // 
            this.openButton_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.openButton_.Location = new System.Drawing.Point(681, 12);
            this.openButton_.Name = "openButton_";
            this.openButton_.Size = new System.Drawing.Size(107, 31);
            this.openButton_.TabIndex = 0;
            this.openButton_.Text = "Open...";
            this.openButton_.UseVisualStyleBackColor = true;
            this.openButton_.Click += new System.EventHandler(this.openButton__Click);
            // 
            // pictureBox_
            // 
            this.pictureBox_.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pictureBox_.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox_.Location = new System.Drawing.Point(2, 2);
            this.pictureBox_.Name = "pictureBox_";
            this.pictureBox_.Size = new System.Drawing.Size(662, 447);
            this.pictureBox_.TabIndex = 2;
            this.pictureBox_.TabStop = false;
            // 
            // propertiesButton_
            // 
            this.propertiesButton_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.propertiesButton_.Enabled = false;
            this.propertiesButton_.Location = new System.Drawing.Point(681, 70);
            this.propertiesButton_.Name = "propertiesButton_";
            this.propertiesButton_.Size = new System.Drawing.Size(107, 31);
            this.propertiesButton_.TabIndex = 3;
            this.propertiesButton_.Text = "Properties...";
            this.propertiesButton_.UseVisualStyleBackColor = true;
            this.propertiesButton_.Click += new System.EventHandler(this.propertiesButton__Click);
            // 
            // MetafileViewerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.propertiesButton_);
            this.Controls.Add(this.pictureBox_);
            this.Controls.Add(this.openButton_);
            this.Name = "MetafileViewerForm";
            this.Text = "Metafile Viewer";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button openButton_;
        private System.Windows.Forms.PictureBox pictureBox_;
        private System.Windows.Forms.Button propertiesButton_;
    }
}

