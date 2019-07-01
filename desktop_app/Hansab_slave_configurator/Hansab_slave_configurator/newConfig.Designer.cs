namespace Hansab_slave_configurator
{
    partial class newConfig
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(newConfig));
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.generate_new_group = new System.Windows.Forms.GroupBox();
            this.Next_button = new System.Windows.Forms.Button();
            this.Floor_count_label = new System.Windows.Forms.Label();
            this.floorCountLabel = new System.Windows.Forms.Label();
            this.ID_label = new System.Windows.Forms.Label();
            this.ID_box = new System.Windows.Forms.ComboBox();
            this.FloorGroupbox1 = new System.Windows.Forms.GroupBox();
            this.numericUpDown3 = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown2 = new System.Windows.Forms.NumericUpDown();
            this.SlaveCountLabel1 = new System.Windows.Forms.Label();
            this.Slave_settings = new System.Windows.Forms.GroupBox();
            this.Type_label = new System.Windows.Forms.Label();
            this.Type_box = new System.Windows.Forms.ComboBox();
            this.SaveButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.LotNameLocationBox = new System.Windows.Forms.TextBox();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.ApplyConfigSettingsButton = new System.Windows.Forms.Button();
            this.testTextBox = new System.Windows.Forms.RichTextBox();
            this.CheckButton = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            this.generate_new_group.SuspendLayout();
            this.FloorGroupbox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).BeginInit();
            this.Slave_settings.SuspendLayout();
            this.SuspendLayout();
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(139, 19);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(45, 20);
            this.numericUpDown1.TabIndex = 0;
            this.numericUpDown1.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // generate_new_group
            // 
            this.generate_new_group.Controls.Add(this.Next_button);
            this.generate_new_group.Controls.Add(this.Floor_count_label);
            this.generate_new_group.Controls.Add(this.numericUpDown1);
            this.generate_new_group.Location = new System.Drawing.Point(148, 60);
            this.generate_new_group.Name = "generate_new_group";
            this.generate_new_group.Size = new System.Drawing.Size(200, 79);
            this.generate_new_group.TabIndex = 1;
            this.generate_new_group.TabStop = false;
            this.generate_new_group.Text = "Generate new";
            // 
            // Next_button
            // 
            this.Next_button.Location = new System.Drawing.Point(57, 48);
            this.Next_button.Name = "Next_button";
            this.Next_button.Size = new System.Drawing.Size(75, 23);
            this.Next_button.TabIndex = 2;
            this.Next_button.TabStop = false;
            this.Next_button.Text = "Create";
            this.Next_button.UseVisualStyleBackColor = true;
            this.Next_button.Click += new System.EventHandler(this.Next_button_Click);
            // 
            // Floor_count_label
            // 
            this.Floor_count_label.AutoSize = true;
            this.Floor_count_label.Location = new System.Drawing.Point(15, 21);
            this.Floor_count_label.Name = "Floor_count_label";
            this.Floor_count_label.Size = new System.Drawing.Size(106, 13);
            this.Floor_count_label.TabIndex = 1;
            this.Floor_count_label.Text = "Enter the floor count:";
            // 
            // floorCountLabel
            // 
            this.floorCountLabel.AutoSize = true;
            this.floorCountLabel.Location = new System.Drawing.Point(108, 22);
            this.floorCountLabel.Name = "floorCountLabel";
            this.floorCountLabel.Size = new System.Drawing.Size(93, 13);
            this.floorCountLabel.TabIndex = 2;
            this.floorCountLabel.Text = "Free space count:";
            // 
            // ID_label
            // 
            this.ID_label.AutoSize = true;
            this.ID_label.Location = new System.Drawing.Point(53, 28);
            this.ID_label.Name = "ID_label";
            this.ID_label.Size = new System.Drawing.Size(21, 13);
            this.ID_label.TabIndex = 3;
            this.ID_label.Text = "ID:";
            // 
            // ID_box
            // 
            this.ID_box.FormattingEnabled = true;
            this.ID_box.Items.AddRange(new object[] {
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "10",
            "11",
            "12",
            "13",
            "14",
            "15"});
            this.ID_box.Location = new System.Drawing.Point(94, 25);
            this.ID_box.Name = "ID_box";
            this.ID_box.Size = new System.Drawing.Size(209, 21);
            this.ID_box.TabIndex = 5;
            // 
            // FloorGroupbox1
            // 
            this.FloorGroupbox1.Controls.Add(this.numericUpDown3);
            this.FloorGroupbox1.Controls.Add(this.numericUpDown2);
            this.FloorGroupbox1.Controls.Add(this.SlaveCountLabel1);
            this.FloorGroupbox1.Controls.Add(this.Slave_settings);
            this.FloorGroupbox1.Controls.Add(this.floorCountLabel);
            this.FloorGroupbox1.Location = new System.Drawing.Point(37, 145);
            this.FloorGroupbox1.Name = "FloorGroupbox1";
            this.FloorGroupbox1.Size = new System.Drawing.Size(406, 222);
            this.FloorGroupbox1.TabIndex = 6;
            this.FloorGroupbox1.TabStop = false;
            this.FloorGroupbox1.Text = "Floor 1 Settings";
            // 
            // numericUpDown3
            // 
            this.numericUpDown3.Location = new System.Drawing.Point(209, 20);
            this.numericUpDown3.Maximum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDown3.Name = "numericUpDown3";
            this.numericUpDown3.Size = new System.Drawing.Size(70, 20);
            this.numericUpDown3.TabIndex = 11;
            this.numericUpDown3.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // numericUpDown2
            // 
            this.numericUpDown2.Location = new System.Drawing.Point(209, 51);
            this.numericUpDown2.Name = "numericUpDown2";
            this.numericUpDown2.Size = new System.Drawing.Size(70, 20);
            this.numericUpDown2.TabIndex = 3;
            this.numericUpDown2.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // SlaveCountLabel1
            // 
            this.SlaveCountLabel1.AutoSize = true;
            this.SlaveCountLabel1.Location = new System.Drawing.Point(112, 53);
            this.SlaveCountLabel1.Name = "SlaveCountLabel1";
            this.SlaveCountLabel1.Size = new System.Drawing.Size(67, 13);
            this.SlaveCountLabel1.TabIndex = 10;
            this.SlaveCountLabel1.Text = "Slave count:";
            // 
            // Slave_settings
            // 
            this.Slave_settings.Controls.Add(this.ID_label);
            this.Slave_settings.Controls.Add(this.Type_label);
            this.Slave_settings.Controls.Add(this.ID_box);
            this.Slave_settings.Controls.Add(this.Type_box);
            this.Slave_settings.Location = new System.Drawing.Point(18, 86);
            this.Slave_settings.Name = "Slave_settings";
            this.Slave_settings.Size = new System.Drawing.Size(372, 100);
            this.Slave_settings.TabIndex = 9;
            this.Slave_settings.TabStop = false;
            this.Slave_settings.Text = "Slave settings";
            // 
            // Type_label
            // 
            this.Type_label.AutoSize = true;
            this.Type_label.Location = new System.Drawing.Point(53, 65);
            this.Type_label.Name = "Type_label";
            this.Type_label.Size = new System.Drawing.Size(34, 13);
            this.Type_label.TabIndex = 8;
            this.Type_label.Text = "Type:";
            // 
            // Type_box
            // 
            this.Type_box.FormattingEnabled = true;
            this.Type_box.Items.AddRange(new object[] {
            "1:  [ ↓ ↑ ]       single bidirectional entrance",
            "2:  [ ↑ ] [ ↓ ]   separate directional entrance and exit",
            "3:  [ ↑ ]          single entrance",
            "4:  [ ↓ ]          single exit"});
            this.Type_box.Location = new System.Drawing.Point(94, 62);
            this.Type_box.Name = "Type_box";
            this.Type_box.Size = new System.Drawing.Size(209, 21);
            this.Type_box.TabIndex = 6;
            // 
            // SaveButton
            // 
            this.SaveButton.Location = new System.Drawing.Point(386, 89);
            this.SaveButton.Name = "SaveButton";
            this.SaveButton.Size = new System.Drawing.Size(75, 23);
            this.SaveButton.TabIndex = 7;
            this.SaveButton.Text = "Send/Save";
            this.SaveButton.UseVisualStyleBackColor = true;
            this.SaveButton.Click += new System.EventHandler(this.SaveButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(175, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(131, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Parking lot location/name:";
            // 
            // LotNameLocationBox
            // 
            this.LotNameLocationBox.Location = new System.Drawing.Point(143, 29);
            this.LotNameLocationBox.Name = "LotNameLocationBox";
            this.LotNameLocationBox.Size = new System.Drawing.Size(206, 20);
            this.LotNameLocationBox.TabIndex = 9;
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileName = "NewConfig";
            this.saveFileDialog1.Filter = "\"Text files (*.txt)|*.txt|All files (*.*)|*.*\"";
            // 
            // ApplyConfigSettingsButton
            // 
            this.ApplyConfigSettingsButton.Location = new System.Drawing.Point(386, 29);
            this.ApplyConfigSettingsButton.Name = "ApplyConfigSettingsButton";
            this.ApplyConfigSettingsButton.Size = new System.Drawing.Size(75, 23);
            this.ApplyConfigSettingsButton.TabIndex = 10;
            this.ApplyConfigSettingsButton.Text = "Apply";
            this.ApplyConfigSettingsButton.UseVisualStyleBackColor = true;
            this.ApplyConfigSettingsButton.Click += new System.EventHandler(this.ApplyConfigSettingsButton_Click);
            // 
            // testTextBox
            // 
            this.testTextBox.Enabled = false;
            this.testTextBox.Location = new System.Drawing.Point(39, 381);
            this.testTextBox.Name = "testTextBox";
            this.testTextBox.Size = new System.Drawing.Size(403, 164);
            this.testTextBox.TabIndex = 11;
            this.testTextBox.Text = "";
            // 
            // CheckButton
            // 
            this.CheckButton.Location = new System.Drawing.Point(386, 60);
            this.CheckButton.Name = "CheckButton";
            this.CheckButton.Size = new System.Drawing.Size(75, 23);
            this.CheckButton.TabIndex = 12;
            this.CheckButton.Text = "Check";
            this.CheckButton.UseVisualStyleBackColor = true;
            this.CheckButton.Click += new System.EventHandler(this.CheckButton_Click);
            // 
            // newConfig
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoScroll = true;
            this.ClientSize = new System.Drawing.Size(484, 561);
            this.Controls.Add(this.CheckButton);
            this.Controls.Add(this.testTextBox);
            this.Controls.Add(this.ApplyConfigSettingsButton);
            this.Controls.Add(this.LotNameLocationBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SaveButton);
            this.Controls.Add(this.FloorGroupbox1);
            this.Controls.Add(this.generate_new_group);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MaximizeBox = false;
            this.Name = "newConfig";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "New Configuration Generator";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            this.generate_new_group.ResumeLayout(false);
            this.generate_new_group.PerformLayout();
            this.FloorGroupbox1.ResumeLayout(false);
            this.FloorGroupbox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown2)).EndInit();
            this.Slave_settings.ResumeLayout(false);
            this.Slave_settings.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.GroupBox generate_new_group;
        private System.Windows.Forms.Button Next_button;
        private System.Windows.Forms.Label Floor_count_label;
        private System.Windows.Forms.Label floorCountLabel;
        private System.Windows.Forms.Label ID_label;
        private System.Windows.Forms.ComboBox ID_box;
        private System.Windows.Forms.GroupBox FloorGroupbox1;
        private System.Windows.Forms.Label Type_label;
        private System.Windows.Forms.ComboBox Type_box;
        private System.Windows.Forms.GroupBox Slave_settings;
        private System.Windows.Forms.NumericUpDown numericUpDown3;
        private System.Windows.Forms.NumericUpDown numericUpDown2;
        private System.Windows.Forms.Label SlaveCountLabel1;
        private System.Windows.Forms.Button SaveButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox LotNameLocationBox;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.Button ApplyConfigSettingsButton;
        private System.Windows.Forms.RichTextBox testTextBox;
        private System.Windows.Forms.Button CheckButton;
    }
}