namespace Hansab_slave_configurator
{
    partial class Login_form
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Login_form));
            this.username_label = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.username_box = new System.Windows.Forms.TextBox();
            this.password_box = new System.Windows.Forms.TextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.login_button = new System.Windows.Forms.Button();
            this.Incorrect_label = new System.Windows.Forms.Label();
            this.ForgotButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // username_label
            // 
            this.username_label.AutoSize = true;
            this.username_label.Location = new System.Drawing.Point(101, 111);
            this.username_label.Name = "username_label";
            this.username_label.Size = new System.Drawing.Size(58, 13);
            this.username_label.TabIndex = 0;
            this.username_label.Text = "Username:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(103, 148);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(56, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Password:";
            // 
            // username_box
            // 
            this.username_box.Location = new System.Drawing.Point(165, 108);
            this.username_box.Name = "username_box";
            this.username_box.Size = new System.Drawing.Size(100, 20);
            this.username_box.TabIndex = 2;
            this.username_box.TextChanged += new System.EventHandler(this.username_box_TextChanged);
            // 
            // password_box
            // 
            this.password_box.Location = new System.Drawing.Point(165, 145);
            this.password_box.Name = "password_box";
            this.password_box.PasswordChar = '*';
            this.password_box.Size = new System.Drawing.Size(100, 20);
            this.password_box.TabIndex = 3;
            this.password_box.TextChanged += new System.EventHandler(this.password_box_TextChanged);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(67, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(250, 64);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pictureBox1.TabIndex = 4;
            this.pictureBox1.TabStop = false;
            // 
            // login_button
            // 
            this.login_button.Location = new System.Drawing.Point(177, 193);
            this.login_button.Name = "login_button";
            this.login_button.Size = new System.Drawing.Size(75, 23);
            this.login_button.TabIndex = 5;
            this.login_button.Text = "Login";
            this.login_button.UseVisualStyleBackColor = true;
            this.login_button.Click += new System.EventHandler(this.login_button_Click);
            // 
            // Incorrect_label
            // 
            this.Incorrect_label.AutoSize = true;
            this.Incorrect_label.ForeColor = System.Drawing.Color.Crimson;
            this.Incorrect_label.Location = new System.Drawing.Point(143, 177);
            this.Incorrect_label.Name = "Incorrect_label";
            this.Incorrect_label.Size = new System.Drawing.Size(151, 13);
            this.Incorrect_label.TabIndex = 6;
            this.Incorrect_label.Text = "Wrong username or password!";
            this.Incorrect_label.Visible = false;
            // 
            // ForgotButton
            // 
            this.ForgotButton.Location = new System.Drawing.Point(165, 235);
            this.ForgotButton.Name = "ForgotButton";
            this.ForgotButton.Size = new System.Drawing.Size(100, 23);
            this.ForgotButton.TabIndex = 7;
            this.ForgotButton.Text = "Forgot Password";
            this.ForgotButton.UseVisualStyleBackColor = true;
            this.ForgotButton.Click += new System.EventHandler(this.ForgotButton_Click);
            // 
            // Login_form
            // 
            this.AcceptButton = this.login_button;
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 270);
            this.Controls.Add(this.ForgotButton);
            this.Controls.Add(this.Incorrect_label);
            this.Controls.Add(this.login_button);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.password_box);
            this.Controls.Add(this.username_box);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.username_label);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Login_form";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Hansab configurator";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label username_label;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox username_box;
        private System.Windows.Forms.TextBox password_box;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button login_button;
        private System.Windows.Forms.Label Incorrect_label;
        private System.Windows.Forms.Button ForgotButton;
    }
}