namespace Hansab_slave_configurator
{
    partial class Main
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main));
            this.Tab_control = new System.Windows.Forms.TabControl();
            this.Main_tab = new System.Windows.Forms.TabPage();
            this.progressLED = new System.Windows.Forms.ProgressBar();
            this.SerialPortBox = new System.Windows.Forms.GroupBox();
            this.label5 = new System.Windows.Forms.Label();
            this.Refresh_button = new System.Windows.Forms.Button();
            this.Apply_button = new System.Windows.Forms.Button();
            this.Restart_button = new System.Windows.Forms.Button();
            this.COM_ports_box = new System.Windows.Forms.ComboBox();
            this.Disonnect_button = new System.Windows.Forms.Button();
            this.Connect_button = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.Online_offline_label = new System.Windows.Forms.Label();
            this.SystemStatus_label = new System.Windows.Forms.Label();
            this.config_tab = new System.Windows.Forms.TabPage();
            this.Current_cfg_label = new System.Windows.Forms.Label();
            this.Current_cfg_box = new System.Windows.Forms.RichTextBox();
            this.Load_new_config_box = new System.Windows.Forms.GroupBox();
            this.newConfig_button = new System.Windows.Forms.Button();
            this.load_button = new System.Windows.Forms.Button();
            this.serial_tab = new System.Windows.Forms.TabPage();
            this.Serial_data_label = new System.Windows.Forms.Label();
            this.test_port_text_box = new System.Windows.Forms.RichTextBox();
            this.error_tab = new System.Windows.Forms.TabPage();
            this.Errors_label = new System.Windows.Forms.Label();
            this.current_errors = new System.Windows.Forms.RichTextBox();
            this.error_help_label = new System.Windows.Forms.Label();
            this.Error_help_box = new System.Windows.Forms.RichTextBox();
            this.help_tab = new System.Windows.Forms.TabPage();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.UserType = new System.Windows.Forms.Label();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.hansab_logo = new System.Windows.Forms.PictureBox();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.label4 = new System.Windows.Forms.Label();
            this.NewUserButton = new System.Windows.Forms.Button();
            this.NewUserText = new System.Windows.Forms.Label();
            this.onButton = new System.Windows.Forms.Button();
            this.offButton = new System.Windows.Forms.Button();
            this.LogOutButton = new System.Windows.Forms.Button();
            this.ChangeUserLabel = new System.Windows.Forms.Label();
            this.Username = new System.Windows.Forms.Label();
            this.Tab_control.SuspendLayout();
            this.Main_tab.SuspendLayout();
            this.SerialPortBox.SuspendLayout();
            this.config_tab.SuspendLayout();
            this.Load_new_config_box.SuspendLayout();
            this.serial_tab.SuspendLayout();
            this.error_tab.SuspendLayout();
            this.help_tab.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.hansab_logo)).BeginInit();
            this.SuspendLayout();
            // 
            // Tab_control
            // 
            this.Tab_control.Controls.Add(this.Main_tab);
            this.Tab_control.Controls.Add(this.config_tab);
            this.Tab_control.Controls.Add(this.serial_tab);
            this.Tab_control.Controls.Add(this.error_tab);
            this.Tab_control.Controls.Add(this.help_tab);
            this.Tab_control.Location = new System.Drawing.Point(177, 12);
            this.Tab_control.Name = "Tab_control";
            this.Tab_control.SelectedIndex = 0;
            this.Tab_control.Size = new System.Drawing.Size(795, 537);
            this.Tab_control.TabIndex = 0;
            // 
            // Main_tab
            // 
            this.Main_tab.Controls.Add(this.offButton);
            this.Main_tab.Controls.Add(this.onButton);
            this.Main_tab.Controls.Add(this.progressLED);
            this.Main_tab.Controls.Add(this.SerialPortBox);
            this.Main_tab.Controls.Add(this.Online_offline_label);
            this.Main_tab.Controls.Add(this.SystemStatus_label);
            this.Main_tab.Location = new System.Drawing.Point(4, 22);
            this.Main_tab.Name = "Main_tab";
            this.Main_tab.Size = new System.Drawing.Size(787, 511);
            this.Main_tab.TabIndex = 4;
            this.Main_tab.Text = "Main";
            this.Main_tab.UseVisualStyleBackColor = true;
            // 
            // progressLED
            // 
            this.progressLED.ForeColor = System.Drawing.Color.FromArgb(((int)(((byte)(0)))), ((int)(((byte)(192)))), ((int)(((byte)(0)))));
            this.progressLED.Location = new System.Drawing.Point(17, 14);
            this.progressLED.Name = "progressLED";
            this.progressLED.Size = new System.Drawing.Size(24, 24);
            this.progressLED.TabIndex = 6;
            // 
            // SerialPortBox
            // 
            this.SerialPortBox.Controls.Add(this.label5);
            this.SerialPortBox.Controls.Add(this.Refresh_button);
            this.SerialPortBox.Controls.Add(this.Apply_button);
            this.SerialPortBox.Controls.Add(this.Restart_button);
            this.SerialPortBox.Controls.Add(this.COM_ports_box);
            this.SerialPortBox.Controls.Add(this.Disonnect_button);
            this.SerialPortBox.Controls.Add(this.Connect_button);
            this.SerialPortBox.Controls.Add(this.label9);
            this.SerialPortBox.Location = new System.Drawing.Point(17, 73);
            this.SerialPortBox.Name = "SerialPortBox";
            this.SerialPortBox.Size = new System.Drawing.Size(259, 240);
            this.SerialPortBox.TabIndex = 5;
            this.SerialPortBox.TabStop = false;
            this.SerialPortBox.Text = "Serial Port Settings";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.label5.Location = new System.Drawing.Point(74, 185);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(113, 16);
            this.label5.TabIndex = 6;
            this.label5.Text = "System Restart";
            // 
            // Refresh_button
            // 
            this.Refresh_button.Location = new System.Drawing.Point(105, 17);
            this.Refresh_button.Name = "Refresh_button";
            this.Refresh_button.Size = new System.Drawing.Size(58, 23);
            this.Refresh_button.TabIndex = 14;
            this.Refresh_button.Text = "Refresh";
            this.Refresh_button.UseVisualStyleBackColor = true;
            // 
            // Apply_button
            // 
            this.Apply_button.Location = new System.Drawing.Point(100, 85);
            this.Apply_button.Name = "Apply_button";
            this.Apply_button.Size = new System.Drawing.Size(63, 24);
            this.Apply_button.TabIndex = 13;
            this.Apply_button.Text = "Apply";
            this.Apply_button.UseVisualStyleBackColor = true;
            // 
            // Restart_button
            // 
            this.Restart_button.Enabled = false;
            this.Restart_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.Restart_button.Location = new System.Drawing.Point(88, 204);
            this.Restart_button.Name = "Restart_button";
            this.Restart_button.Size = new System.Drawing.Size(75, 23);
            this.Restart_button.TabIndex = 4;
            this.Restart_button.Text = "Restart";
            this.Restart_button.UseVisualStyleBackColor = true;
            this.Restart_button.Click += new System.EventHandler(this.Restart_button_Click);
            // 
            // COM_ports_box
            // 
            this.COM_ports_box.FormattingEnabled = true;
            this.COM_ports_box.Location = new System.Drawing.Point(84, 49);
            this.COM_ports_box.Name = "COM_ports_box";
            this.COM_ports_box.Size = new System.Drawing.Size(103, 21);
            this.COM_ports_box.TabIndex = 5;
            // 
            // Disonnect_button
            // 
            this.Disonnect_button.Location = new System.Drawing.Point(137, 115);
            this.Disonnect_button.Name = "Disonnect_button";
            this.Disonnect_button.Size = new System.Drawing.Size(75, 23);
            this.Disonnect_button.TabIndex = 2;
            this.Disonnect_button.Text = "Disconnect";
            this.Disonnect_button.UseVisualStyleBackColor = true;
            // 
            // Connect_button
            // 
            this.Connect_button.Location = new System.Drawing.Point(56, 115);
            this.Connect_button.Name = "Connect_button";
            this.Connect_button.Size = new System.Drawing.Size(75, 23);
            this.Connect_button.TabIndex = 1;
            this.Connect_button.Text = "Connect";
            this.Connect_button.UseVisualStyleBackColor = true;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(18, 52);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(60, 13);
            this.label9.TabIndex = 0;
            this.label9.Text = "Port Name:";
            // 
            // Online_offline_label
            // 
            this.Online_offline_label.AutoSize = true;
            this.Online_offline_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.Online_offline_label.Location = new System.Drawing.Point(171, 14);
            this.Online_offline_label.Name = "Online_offline_label";
            this.Online_offline_label.Size = new System.Drawing.Size(184, 24);
            this.Online_offline_label.TabIndex = 2;
            this.Online_offline_label.Text = "Offline/Disconnected";
            // 
            // SystemStatus_label
            // 
            this.SystemStatus_label.AutoSize = true;
            this.SystemStatus_label.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.SystemStatus_label.Location = new System.Drawing.Point(47, 15);
            this.SystemStatus_label.Name = "SystemStatus_label";
            this.SystemStatus_label.Size = new System.Drawing.Size(128, 24);
            this.SystemStatus_label.TabIndex = 1;
            this.SystemStatus_label.Text = "System status:";
            // 
            // config_tab
            // 
            this.config_tab.Controls.Add(this.Current_cfg_label);
            this.config_tab.Controls.Add(this.Current_cfg_box);
            this.config_tab.Controls.Add(this.Load_new_config_box);
            this.config_tab.Location = new System.Drawing.Point(4, 22);
            this.config_tab.Name = "config_tab";
            this.config_tab.Padding = new System.Windows.Forms.Padding(3);
            this.config_tab.Size = new System.Drawing.Size(787, 511);
            this.config_tab.TabIndex = 0;
            this.config_tab.Text = "Configuration";
            this.config_tab.UseVisualStyleBackColor = true;
            // 
            // Current_cfg_label
            // 
            this.Current_cfg_label.AutoSize = true;
            this.Current_cfg_label.Location = new System.Drawing.Point(20, 98);
            this.Current_cfg_label.Name = "Current_cfg_label";
            this.Current_cfg_label.Size = new System.Drawing.Size(108, 13);
            this.Current_cfg_label.TabIndex = 4;
            this.Current_cfg_label.Text = "Current configuration:";
            // 
            // Current_cfg_box
            // 
            this.Current_cfg_box.Location = new System.Drawing.Point(17, 114);
            this.Current_cfg_box.Name = "Current_cfg_box";
            this.Current_cfg_box.Size = new System.Drawing.Size(744, 376);
            this.Current_cfg_box.TabIndex = 3;
            this.Current_cfg_box.Text = "";
            // 
            // Load_new_config_box
            // 
            this.Load_new_config_box.Controls.Add(this.newConfig_button);
            this.Load_new_config_box.Controls.Add(this.load_button);
            this.Load_new_config_box.Location = new System.Drawing.Point(291, 24);
            this.Load_new_config_box.Name = "Load_new_config_box";
            this.Load_new_config_box.Size = new System.Drawing.Size(169, 59);
            this.Load_new_config_box.TabIndex = 2;
            this.Load_new_config_box.TabStop = false;
            this.Load_new_config_box.Text = "Load/New Configuration file";
            // 
            // newConfig_button
            // 
            this.newConfig_button.Location = new System.Drawing.Point(87, 24);
            this.newConfig_button.Name = "newConfig_button";
            this.newConfig_button.Size = new System.Drawing.Size(75, 23);
            this.newConfig_button.TabIndex = 2;
            this.newConfig_button.Text = "New";
            this.newConfig_button.UseVisualStyleBackColor = true;
            this.newConfig_button.Click += new System.EventHandler(this.newConfig_button_Click);
            // 
            // load_button
            // 
            this.load_button.Location = new System.Drawing.Point(6, 24);
            this.load_button.Name = "load_button";
            this.load_button.Size = new System.Drawing.Size(75, 23);
            this.load_button.TabIndex = 0;
            this.load_button.Text = "Load";
            this.load_button.UseVisualStyleBackColor = true;
            this.load_button.Click += new System.EventHandler(this.load_button_Click);
            // 
            // serial_tab
            // 
            this.serial_tab.Controls.Add(this.Serial_data_label);
            this.serial_tab.Controls.Add(this.test_port_text_box);
            this.serial_tab.Location = new System.Drawing.Point(4, 22);
            this.serial_tab.Name = "serial_tab";
            this.serial_tab.Padding = new System.Windows.Forms.Padding(3);
            this.serial_tab.Size = new System.Drawing.Size(787, 511);
            this.serial_tab.TabIndex = 1;
            this.serial_tab.Text = "Log";
            this.serial_tab.UseVisualStyleBackColor = true;
            // 
            // Serial_data_label
            // 
            this.Serial_data_label.AutoSize = true;
            this.Serial_data_label.Location = new System.Drawing.Point(24, 19);
            this.Serial_data_label.Name = "Serial_data_label";
            this.Serial_data_label.Size = new System.Drawing.Size(62, 13);
            this.Serial_data_label.TabIndex = 4;
            this.Serial_data_label.Text = "Serial Data:";
            // 
            // test_port_text_box
            // 
            this.test_port_text_box.Enabled = false;
            this.test_port_text_box.Location = new System.Drawing.Point(27, 35);
            this.test_port_text_box.Name = "test_port_text_box";
            this.test_port_text_box.Size = new System.Drawing.Size(729, 410);
            this.test_port_text_box.TabIndex = 3;
            this.test_port_text_box.Text = "";
            // 
            // error_tab
            // 
            this.error_tab.Controls.Add(this.Errors_label);
            this.error_tab.Controls.Add(this.current_errors);
            this.error_tab.Controls.Add(this.error_help_label);
            this.error_tab.Controls.Add(this.Error_help_box);
            this.error_tab.Location = new System.Drawing.Point(4, 22);
            this.error_tab.Name = "error_tab";
            this.error_tab.Padding = new System.Windows.Forms.Padding(3);
            this.error_tab.Size = new System.Drawing.Size(787, 511);
            this.error_tab.TabIndex = 2;
            this.error_tab.Text = "Errors";
            this.error_tab.UseVisualStyleBackColor = true;
            // 
            // Errors_label
            // 
            this.Errors_label.AutoSize = true;
            this.Errors_label.Location = new System.Drawing.Point(12, 17);
            this.Errors_label.Name = "Errors_label";
            this.Errors_label.Size = new System.Drawing.Size(73, 13);
            this.Errors_label.TabIndex = 3;
            this.Errors_label.Text = "Current errors:";
            // 
            // current_errors
            // 
            this.current_errors.Enabled = false;
            this.current_errors.Location = new System.Drawing.Point(15, 33);
            this.current_errors.Name = "current_errors";
            this.current_errors.Size = new System.Drawing.Size(757, 277);
            this.current_errors.TabIndex = 2;
            this.current_errors.Text = "None! All good! :)";
            // 
            // error_help_label
            // 
            this.error_help_label.AutoSize = true;
            this.error_help_label.Location = new System.Drawing.Point(12, 332);
            this.error_help_label.Name = "error_help_label";
            this.error_help_label.Size = new System.Drawing.Size(95, 13);
            this.error_help_label.TabIndex = 1;
            this.error_help_label.Text = "List of Error codes:";
            // 
            // Error_help_box
            // 
            this.Error_help_box.Enabled = false;
            this.Error_help_box.Location = new System.Drawing.Point(15, 348);
            this.Error_help_box.Name = "Error_help_box";
            this.Error_help_box.Size = new System.Drawing.Size(757, 151);
            this.Error_help_box.TabIndex = 0;
            this.Error_help_box.Text = resources.GetString("Error_help_box.Text");
            // 
            // help_tab
            // 
            this.help_tab.Controls.Add(this.richTextBox1);
            this.help_tab.Location = new System.Drawing.Point(4, 22);
            this.help_tab.Name = "help_tab";
            this.help_tab.Padding = new System.Windows.Forms.Padding(3);
            this.help_tab.Size = new System.Drawing.Size(787, 511);
            this.help_tab.TabIndex = 3;
            this.help_tab.Text = "Help";
            this.help_tab.UseVisualStyleBackColor = true;
            // 
            // richTextBox1
            // 
            this.richTextBox1.Enabled = false;
            this.richTextBox1.Location = new System.Drawing.Point(6, 20);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(775, 485);
            this.richTextBox1.TabIndex = 0;
            this.richTextBox1.Text = resources.GetString("richTextBox1.Text");
            // 
            // UserType
            // 
            this.UserType.AutoSize = true;
            this.UserType.Font = new System.Drawing.Font("Microsoft Sans Serif", 36F, ((System.Drawing.FontStyle)((System.Drawing.FontStyle.Bold | System.Drawing.FontStyle.Underline))), System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.UserType.ForeColor = System.Drawing.Color.Crimson;
            this.UserType.Location = new System.Drawing.Point(11, 12);
            this.UserType.Name = "UserType";
            this.UserType.Size = new System.Drawing.Size(160, 55);
            this.UserType.TabIndex = 1;
            this.UserType.Text = "admin";
            // 
            // serialPort1
            // 
            this.serialPort1.PortName = "COM8";
            // 
            // hansab_logo
            // 
            this.hansab_logo.Image = ((System.Drawing.Image)(resources.GetObject("hansab_logo.Image")));
            this.hansab_logo.Location = new System.Drawing.Point(8, 474);
            this.hansab_logo.Name = "hansab_logo";
            this.hansab_logo.Size = new System.Drawing.Size(163, 50);
            this.hansab_logo.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.hansab_logo.TabIndex = 2;
            this.hansab_logo.TabStop = false;
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "Configuration_file.txt";
            this.openFileDialog1.Filter = "\"Text files (*.txt)|*.txt|All files (*.*)|*.*\"";
            this.openFileDialog1.Title = "\"Open text file\"";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(49, 532);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(69, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Version 1.0.0";
            // 
            // NewUserButton
            // 
            this.NewUserButton.Location = new System.Drawing.Point(52, 410);
            this.NewUserButton.Name = "NewUserButton";
            this.NewUserButton.Size = new System.Drawing.Size(75, 23);
            this.NewUserButton.TabIndex = 4;
            this.NewUserButton.Text = "Add";
            this.NewUserButton.UseVisualStyleBackColor = true;
            this.NewUserButton.Click += new System.EventHandler(this.NewUserButton_Click);
            // 
            // NewUserText
            // 
            this.NewUserText.AutoSize = true;
            this.NewUserText.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.NewUserText.Location = new System.Drawing.Point(42, 391);
            this.NewUserText.Name = "NewUserText";
            this.NewUserText.Size = new System.Drawing.Size(95, 16);
            this.NewUserText.TabIndex = 5;
            this.NewUserText.Text = "Add New User";
            // 
            // onButton
            // 
            this.onButton.Location = new System.Drawing.Point(353, 50);
            this.onButton.Name = "onButton";
            this.onButton.Size = new System.Drawing.Size(36, 23);
            this.onButton.TabIndex = 7;
            this.onButton.Text = "ON";
            this.onButton.UseVisualStyleBackColor = true;
            this.onButton.Click += new System.EventHandler(this.onButton_Click);
            // 
            // offButton
            // 
            this.offButton.Location = new System.Drawing.Point(395, 50);
            this.offButton.Name = "offButton";
            this.offButton.Size = new System.Drawing.Size(37, 23);
            this.offButton.TabIndex = 8;
            this.offButton.Text = "OFF";
            this.offButton.UseVisualStyleBackColor = true;
            this.offButton.Click += new System.EventHandler(this.offButton_Click);
            // 
            // LogOutButton
            // 
            this.LogOutButton.Location = new System.Drawing.Point(52, 148);
            this.LogOutButton.Name = "LogOutButton";
            this.LogOutButton.Size = new System.Drawing.Size(75, 23);
            this.LogOutButton.TabIndex = 6;
            this.LogOutButton.Text = "Log Out";
            this.LogOutButton.UseVisualStyleBackColor = true;
            this.LogOutButton.Click += new System.EventHandler(this.LogOutButton_Click);
            // 
            // ChangeUserLabel
            // 
            this.ChangeUserLabel.AutoSize = true;
            this.ChangeUserLabel.Location = new System.Drawing.Point(58, 130);
            this.ChangeUserLabel.Name = "ChangeUserLabel";
            this.ChangeUserLabel.Size = new System.Drawing.Size(69, 13);
            this.ChangeUserLabel.TabIndex = 7;
            this.ChangeUserLabel.Text = "Change User";
            // 
            // Username
            // 
            this.Username.AutoSize = true;
            this.Username.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(186)));
            this.Username.Location = new System.Drawing.Point(57, 79);
            this.Username.Name = "Username";
            this.Username.Size = new System.Drawing.Size(70, 24);
            this.Username.TabIndex = 8;
            this.Username.Text = "aaaaaa";
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(984, 561);
            this.Controls.Add(this.Username);
            this.Controls.Add(this.ChangeUserLabel);
            this.Controls.Add(this.LogOutButton);
            this.Controls.Add(this.NewUserText);
            this.Controls.Add(this.NewUserButton);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.hansab_logo);
            this.Controls.Add(this.UserType);
            this.Controls.Add(this.Tab_control);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Hansab configurator";
            this.Tab_control.ResumeLayout(false);
            this.Main_tab.ResumeLayout(false);
            this.Main_tab.PerformLayout();
            this.SerialPortBox.ResumeLayout(false);
            this.SerialPortBox.PerformLayout();
            this.config_tab.ResumeLayout(false);
            this.config_tab.PerformLayout();
            this.Load_new_config_box.ResumeLayout(false);
            this.serial_tab.ResumeLayout(false);
            this.serial_tab.PerformLayout();
            this.error_tab.ResumeLayout(false);
            this.error_tab.PerformLayout();
            this.help_tab.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.hansab_logo)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl Tab_control;
        private System.Windows.Forms.TabPage config_tab;
        private System.Windows.Forms.TabPage serial_tab;
        private System.Windows.Forms.Label UserType;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.TabPage error_tab;
        private System.Windows.Forms.TabPage help_tab;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.Label Errors_label;
        private System.Windows.Forms.RichTextBox current_errors;
        private System.Windows.Forms.Label error_help_label;
        private System.Windows.Forms.RichTextBox Error_help_box;
        private System.Windows.Forms.RichTextBox test_port_text_box;
        private System.Windows.Forms.Label Serial_data_label;
        private System.Windows.Forms.TabPage Main_tab;
        private System.Windows.Forms.GroupBox Load_new_config_box;
        private System.Windows.Forms.Button load_button;
        private System.Windows.Forms.PictureBox hansab_logo;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.Label Current_cfg_label;
        private System.Windows.Forms.RichTextBox Current_cfg_box;
        private System.Windows.Forms.Button newConfig_button;
        private System.Windows.Forms.Label Online_offline_label;
        private System.Windows.Forms.Label SystemStatus_label;
        private System.Windows.Forms.Button Restart_button;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.GroupBox SerialPortBox;
        private System.Windows.Forms.Button Refresh_button;
        private System.Windows.Forms.Button Apply_button;
        private System.Windows.Forms.ComboBox COM_ports_box;
        private System.Windows.Forms.Button Disonnect_button;
        private System.Windows.Forms.Button Connect_button;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button NewUserButton;
        private System.Windows.Forms.Label NewUserText;
        private System.Windows.Forms.ProgressBar progressLED;
        private System.Windows.Forms.Button offButton;
        private System.Windows.Forms.Button onButton;
        private System.Windows.Forms.Button LogOutButton;
        private System.Windows.Forms.Label ChangeUserLabel;
        private System.Windows.Forms.Label Username;
    }
}