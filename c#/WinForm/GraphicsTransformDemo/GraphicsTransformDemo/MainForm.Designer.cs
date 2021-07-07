
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
            this.xLabel_ = new System.Windows.Forms.Label();
            this.xNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.yLabel_ = new System.Windows.Forms.Label();
            this.yNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.heightNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.heightLabel_ = new System.Windows.Forms.Label();
            this.widthNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.widthLabel_ = new System.Windows.Forms.Label();
            this.angleNumericUpDown_ = new System.Windows.Forms.NumericUpDown();
            this.angleLabel_ = new System.Windows.Forms.Label();
            this.timer_ = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.xNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.yNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.heightNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.widthNumericUpDown_)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.angleNumericUpDown_)).BeginInit();
            this.SuspendLayout();
            // 
            // xLabel_
            // 
            this.xLabel_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.xLabel_.AutoSize = true;
            this.xLabel_.Location = new System.Drawing.Point(733, 9);
            this.xLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.xLabel_.Name = "xLabel_";
            this.xLabel_.Size = new System.Drawing.Size(32, 21);
            this.xLabel_.TabIndex = 0;
            this.xLabel_.Text = "X:";
            // 
            // xNumericUpDown_
            // 
            this.xNumericUpDown_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.xNumericUpDown_.Location = new System.Drawing.Point(774, 7);
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
            this.xNumericUpDown_.TabIndex = 1;
            this.xNumericUpDown_.ValueChanged += new System.EventHandler(this.xNumericUpDown__ValueChanged);
            // 
            // yLabel_
            // 
            this.yLabel_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.yLabel_.AutoSize = true;
            this.yLabel_.Location = new System.Drawing.Point(733, 46);
            this.yLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.yLabel_.Name = "yLabel_";
            this.yLabel_.Size = new System.Drawing.Size(32, 21);
            this.yLabel_.TabIndex = 2;
            this.yLabel_.Text = "Y:";
            // 
            // yNumericUpDown_
            // 
            this.yNumericUpDown_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.yNumericUpDown_.Location = new System.Drawing.Point(774, 44);
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
            this.yNumericUpDown_.TabIndex = 3;
            this.yNumericUpDown_.ValueChanged += new System.EventHandler(this.yNumericUpDown__ValueChanged);
            // 
            // heightNumericUpDown_
            // 
            this.heightNumericUpDown_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.heightNumericUpDown_.Location = new System.Drawing.Point(774, 118);
            this.heightNumericUpDown_.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.heightNumericUpDown_.Name = "heightNumericUpDown_";
            this.heightNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.heightNumericUpDown_.TabIndex = 7;
            this.heightNumericUpDown_.Value = new decimal(new int[] {
            80,
            0,
            0,
            0});
            this.heightNumericUpDown_.ValueChanged += new System.EventHandler(this.heightNumericUpDown__ValueChanged);
            // 
            // heightLabel_
            // 
            this.heightLabel_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.heightLabel_.AutoSize = true;
            this.heightLabel_.Location = new System.Drawing.Point(733, 120);
            this.heightLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.heightLabel_.Name = "heightLabel_";
            this.heightLabel_.Size = new System.Drawing.Size(32, 21);
            this.heightLabel_.TabIndex = 6;
            this.heightLabel_.Text = "H:";
            // 
            // widthNumericUpDown_
            // 
            this.widthNumericUpDown_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.widthNumericUpDown_.Location = new System.Drawing.Point(774, 81);
            this.widthNumericUpDown_.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.widthNumericUpDown_.Name = "widthNumericUpDown_";
            this.widthNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.widthNumericUpDown_.TabIndex = 5;
            this.widthNumericUpDown_.Value = new decimal(new int[] {
            120,
            0,
            0,
            0});
            this.widthNumericUpDown_.ValueChanged += new System.EventHandler(this.widthNumericUpDown__ValueChanged);
            // 
            // widthLabel_
            // 
            this.widthLabel_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.widthLabel_.AutoSize = true;
            this.widthLabel_.Location = new System.Drawing.Point(733, 83);
            this.widthLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.widthLabel_.Name = "widthLabel_";
            this.widthLabel_.Size = new System.Drawing.Size(32, 21);
            this.widthLabel_.TabIndex = 4;
            this.widthLabel_.Text = "W:";
            // 
            // angleNumericUpDown_
            // 
            this.angleNumericUpDown_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.angleNumericUpDown_.Location = new System.Drawing.Point(774, 155);
            this.angleNumericUpDown_.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
            this.angleNumericUpDown_.Name = "angleNumericUpDown_";
            this.angleNumericUpDown_.Size = new System.Drawing.Size(100, 31);
            this.angleNumericUpDown_.TabIndex = 9;
            this.angleNumericUpDown_.ValueChanged += new System.EventHandler(this.angleNumericUpDown__ValueChanged);
            // 
            // angleLabel_
            // 
            this.angleLabel_.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.angleLabel_.AutoSize = true;
            this.angleLabel_.Location = new System.Drawing.Point(733, 157);
            this.angleLabel_.Margin = new System.Windows.Forms.Padding(6, 0, 6, 0);
            this.angleLabel_.Name = "angleLabel_";
            this.angleLabel_.Size = new System.Drawing.Size(32, 21);
            this.angleLabel_.TabIndex = 8;
            this.angleLabel_.Text = "A:";
            // 
            // timer_
            // 
            this.timer_.Enabled = true;
            this.timer_.Tick += new System.EventHandler(this.timer__Tick);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(11F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(890, 420);
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
            this.Font = new System.Drawing.Font("SimSun", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.Margin = new System.Windows.Forms.Padding(6, 5, 6, 5);
            this.Name = "MainForm";
            this.Text = "Form";
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.Paint += new System.Windows.Forms.PaintEventHandler(this.MainForm_Paint);
            this.Layout += new System.Windows.Forms.LayoutEventHandler(this.MainForm_Layout);
            this.Resize += new System.EventHandler(this.MainForm_Resize);
            ((System.ComponentModel.ISupportInitialize)(this.xNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.yNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.heightNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.widthNumericUpDown_)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.angleNumericUpDown_)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label xLabel_;
        private System.Windows.Forms.NumericUpDown xNumericUpDown_;
        private System.Windows.Forms.Label yLabel_;
        private System.Windows.Forms.NumericUpDown yNumericUpDown_;
        private System.Windows.Forms.NumericUpDown heightNumericUpDown_;
        private System.Windows.Forms.Label heightLabel_;
        private System.Windows.Forms.NumericUpDown widthNumericUpDown_;
        private System.Windows.Forms.Label widthLabel_;
        private System.Windows.Forms.NumericUpDown angleNumericUpDown_;
        private System.Windows.Forms.Label angleLabel_;
        private System.Windows.Forms.Timer timer_;
    }
}

