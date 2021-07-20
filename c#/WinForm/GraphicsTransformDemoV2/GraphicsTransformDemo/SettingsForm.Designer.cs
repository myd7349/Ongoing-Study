
namespace GraphicsTransformDemo
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
            this.angleNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.angleLabel_ = new System.Windows.Forms.Label();
            this.heightNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.heightLabel_ = new System.Windows.Forms.Label();
            this.widthNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.widthLabel_ = new System.Windows.Forms.Label();
            this.yNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.yLabel_ = new System.Windows.Forms.Label();
            this.xNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.xLabel_ = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.angleNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.heightNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.widthNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.yNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.xNumericUpDown_)).BeginInit();
            this.SuspendLayout();
            // 
            // angleNumericUpDown_
            // 
            this.angleNumericUpDown_.Location = new System.Drawing.Point(56, 155);
            this.angleNumericUpDown_.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
            this.angleNumericUpDown_.Name = "angleNumericUpDown_";
            this.angleNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.angleNumericUpDown_.TabIndex = 19;
            // 
            // angleLabel_
            // 
            this.angleLabel_.AutoSize = true;
            this.angleLabel_.Location = new System.Drawing.Point(15, 157);
            this.angleLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.angleLabel_.Name = "angleLabel_";
            this.angleLabel_.Size = new System.Drawing.Size(32, 21);
            this.angleLabel_.TabIndex = 18;
            this.angleLabel_.Text = "A:";
            // 
            // heightNumericUpDown_
            // 
            this.heightNumericUpDown_.Location = new System.Drawing.Point(56, 118);
            this.heightNumericUpDown_.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.heightNumericUpDown_.Name = "heightNumericUpDown_";
            this.heightNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.heightNumericUpDown_.TabIndex = 17;
            this.heightNumericUpDown_.Value = new decimal(new int[] {
            80,
            0,
            0,
            0});
            // 
            // heightLabel_
            // 
            this.heightLabel_.AutoSize = true;
            this.heightLabel_.Location = new System.Drawing.Point(15, 120);
            this.heightLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.heightLabel_.Name = "heightLabel_";
            this.heightLabel_.Size = new System.Drawing.Size(32, 21);
            this.heightLabel_.TabIndex = 16;
            this.heightLabel_.Text = "H:";
            // 
            // widthNumericUpDown_
            // 
            this.widthNumericUpDown_.Location = new System.Drawing.Point(56, 81);
            this.widthNumericUpDown_.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.widthNumericUpDown_.Name = "widthNumericUpDown_";
            this.widthNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.widthNumericUpDown_.TabIndex = 15;
            this.widthNumericUpDown_.Value = new decimal(new int[] {
            120,
            0,
            0,
            0});
            // 
            // widthLabel_
            // 
            this.widthLabel_.AutoSize = true;
            this.widthLabel_.Location = new System.Drawing.Point(15, 83);
            this.widthLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.widthLabel_.Name = "widthLabel_";
            this.widthLabel_.Size = new System.Drawing.Size(32, 21);
            this.widthLabel_.TabIndex = 14;
            this.widthLabel_.Text = "W:";
            // 
            // yNumericUpDown_
            // 
            this.yNumericUpDown_.Location = new System.Drawing.Point(56, 44);
            this.yNumericUpDown_.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this.yNumericUpDown_.Minimum = new decimal(new int[] {
            5000,
            0,
            0,
            -2147483648});
            this.yNumericUpDown_.Name = "yNumericUpDown_";
            this.yNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.yNumericUpDown_.TabIndex = 13;
            // 
            // yLabel_
            // 
            this.yLabel_.AutoSize = true;
            this.yLabel_.Location = new System.Drawing.Point(15, 46);
            this.yLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.yLabel_.Name = "yLabel_";
            this.yLabel_.Size = new System.Drawing.Size(32, 21);
            this.yLabel_.TabIndex = 12;
            this.yLabel_.Text = "Y:";
            // 
            // xNumericUpDown_
            // 
            this.xNumericUpDown_.Location = new System.Drawing.Point(56, 7);
            this.xNumericUpDown_.Maximum = new decimal(new int[] {
            5000,
            0,
            0,
            0});
            this.xNumericUpDown_.Minimum = new decimal(new int[] {
            5000,
            0,
            0,
            -2147483648});
            this.xNumericUpDown_.Name = "xNumericUpDown_";
            this.xNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.xNumericUpDown_.TabIndex = 11;
            // 
            // xLabel_
            // 
            this.xLabel_.AutoSize = true;
            this.xLabel_.Location = new System.Drawing.Point(15, 9);
            this.xLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.xLabel_.Name = "xLabel_";
            this.xLabel_.Size = new System.Drawing.Size(32, 21);
            this.xLabel_.TabIndex = 10;
            this.xLabel_.Text = "X:";
            // 
            // SettingsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(179, 222);
            this.Controls.Add(this.angleNumericUpDown_);
            this.Controls.Add(this.angleLabel_);
            this.Controls.Add(this.heightNumericUpDown_);
            this.Controls.Add(this.heightLabel_);
            this.Controls.Add(this.widthNumericUpDown_);
            this.Controls.Add(this.widthLabel_);
            this.Controls.Add(this.yNumericUpDown_);
            this.Controls.Add(this.yLabel_);
            this.Controls.Add(this.xNumericUpDown_);
            this.Controls.Add(this.xLabel_);
            this.Font = new System.Drawing.Font("SimSun", 15.75F);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(6, 5, 6, 5);
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "SettingsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "Settings";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SettingsForm_FormClosing);
            this.VisibleChanged += new System.EventHandler(this.SettingsForm_VisibleChanged);
            ((System.ComponentModel.ISupportInitialize)(this.angleNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.heightNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.widthNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.yNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.xNumericUpDown_)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown angleNumericUpDown_;
        private System.Windows.Forms.Label angleLabel_;
        private System.Windows.Forms.NumericUpDown heightNumericUpDown_;
        private System.Windows.Forms.Label heightLabel_;
        private System.Windows.Forms.NumericUpDown widthNumericUpDown_;
        private System.Windows.Forms.Label widthLabel_;
        private System.Windows.Forms.NumericUpDown yNumericUpDown_;
        private System.Windows.Forms.Label yLabel_;
        private System.Windows.Forms.NumericUpDown xNumericUpDown_;
        private System.Windows.Forms.Label xLabel_;
    }
}
