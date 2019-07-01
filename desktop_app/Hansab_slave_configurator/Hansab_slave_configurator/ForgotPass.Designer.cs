namespace Hansab_slave_configurator
{
    partial class ForgotPass
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(ForgotPass));
            this.Contacts_label = new System.Windows.Forms.Label();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.ID_Label = new System.Windows.Forms.Label();
            this.ID_Box = new System.Windows.Forms.TextBox();
            this.NewPassLabel = new System.Windows.Forms.Label();
            this.PasswordBox = new System.Windows.Forms.TextBox();
            this.ChangeButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // Contacts_label
            // 
            this.Contacts_label.AutoSize = true;
            this.Contacts_label.Location = new System.Drawing.Point(23, 218);
            this.Contacts_label.Name = "Contacts_label";
            this.Contacts_label.Size = new System.Drawing.Size(52, 13);
            this.Contacts_label.TabIndex = 0;
            this.Contacts_label.Text = "Contacts:";
            // 
            // richTextBox1
            // 
            this.richTextBox1.Enabled = false;
            this.richTextBox1.Location = new System.Drawing.Point(26, 234);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(234, 66);
            this.richTextBox1.TabIndex = 1;
            this.richTextBox1.Text = "+37127845921 - Jānis Jānis\n+37128355928 - Brālis Jānis\n+37127845929 - Andris Jāni" +
    "s\n+37127845923 - Baņa Jānis";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 306);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(258, 66);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 2;
            this.pictureBox1.TabStop = false;
            // 
            // ID_Label
            // 
            this.ID_Label.AutoSize = true;
            this.ID_Label.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.ID_Label.Location = new System.Drawing.Point(97, 16);
            this.ID_Label.Name = "ID_Label";
            this.ID_Label.Size = new System.Drawing.Size(90, 25);
            this.ID_Label.TabIndex = 3;
            this.ID_Label.Text = "Your ID:";
            this.ID_Label.Click += new System.EventHandler(this.ID_Label_Click);
            // 
            // ID_Box
            // 
            this.ID_Box.BackColor = System.Drawing.Color.White;
            this.ID_Box.Enabled = false;
            this.ID_Box.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.ID_Box.Location = new System.Drawing.Point(76, 44);
            this.ID_Box.Name = "ID_Box";
            this.ID_Box.Size = new System.Drawing.Size(131, 47);
            this.ID_Box.TabIndex = 4;
            // 
            // NewPassLabel
            // 
            this.NewPassLabel.AutoSize = true;
            this.NewPassLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.NewPassLabel.Location = new System.Drawing.Point(54, 117);
            this.NewPassLabel.Name = "NewPassLabel";
            this.NewPassLabel.Size = new System.Drawing.Size(191, 20);
            this.NewPassLabel.TabIndex = 5;
            this.NewPassLabel.Text = "Enter your new password:";
            this.NewPassLabel.Click += new System.EventHandler(this.NewPassLabel_Click);
            // 
            // PasswordBox
            // 
            this.PasswordBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.PasswordBox.Location = new System.Drawing.Point(76, 140);
            this.PasswordBox.Name = "PasswordBox";
            this.PasswordBox.PasswordChar = '*';
            this.PasswordBox.Size = new System.Drawing.Size(131, 26);
            this.PasswordBox.TabIndex = 6;
            this.PasswordBox.TextChanged += new System.EventHandler(this.PasswordBox_TextChanged);
            // 
            // ChangeButton
            // 
            this.ChangeButton.Location = new System.Drawing.Point(102, 183);
            this.ChangeButton.Name = "ChangeButton";
            this.ChangeButton.Size = new System.Drawing.Size(75, 23);
            this.ChangeButton.TabIndex = 7;
            this.ChangeButton.Text = "Change";
            this.ChangeButton.UseVisualStyleBackColor = true;
            this.ChangeButton.Click += new System.EventHandler(this.ChangeButton_Click);
            // 
            // ForgotPass
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(288, 384);
            this.Controls.Add(this.ChangeButton);
            this.Controls.Add(this.PasswordBox);
            this.Controls.Add(this.NewPassLabel);
            this.Controls.Add(this.ID_Box);
            this.Controls.Add(this.ID_Label);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.Contacts_label);
            this.MaximizeBox = false;
            this.Name = "ForgotPass";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "ForgotPass";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label Contacts_label;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label ID_Label;
        private System.Windows.Forms.TextBox ID_Box;
        private System.Windows.Forms.Label NewPassLabel;
        private System.Windows.Forms.TextBox PasswordBox;
        private System.Windows.Forms.Button ChangeButton;
    }
}