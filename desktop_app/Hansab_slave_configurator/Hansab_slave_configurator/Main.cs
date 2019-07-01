using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;

namespace Hansab_slave_configurator
{
    public partial class Main : Form
    {
        Boolean apply = false;
        Boolean _continue = false;
        string serialPorts;
        string textFromFile;
        public Main(string type)
        {
            InitializeComponent();
            getPortNames();
            if (type == "admin")
            {
                UserType.Text = "Admin";
            }
            else if (type == "guest")
            {               
                UserType.Text = "Guest";
                config_tab.Text = "--";
                Load_new_config_box.Visible = false;
                Current_cfg_box.Visible = false;
                Current_cfg_label.Visible = false;
                NewUserButton.Visible = false;
                NewUserText.Visible = false;

            }
        }


        private void applyButton_Click(object sender, EventArgs e)
        {
            SetSerialSettings();
            test_port_text_box.AppendText("Serial settings: \n");
            test_port_text_box.AppendText(COM_ports_box.Text + "\n");
            apply = true;
        }

        private void connect_button_Click(object sender, EventArgs e)
        {
            if (apply == true)
            {
                _continue = true;
                serialPort1.Open();
                listen();
                progressLED.Value = 100;
            }
        }

        private void Disconnect_button_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                _continue = false;
                apply = false;
                serialPort1.Close();
                progressLED.Value = 0;
            }
        }

        private void listen() {

            progressLED.Value = 100;

            while (_continue) {

                string message = serialPort1.ReadLine();
                test_port_text_box.AppendText(message);
            }
        }
    
        private void refresh_button_Click(object sender, EventArgs e)
        {
            COM_ports_box.Text = "";
            getPortNames();

        }

        private void COM_ports_box_SelectedIndexChanged(object sender, EventArgs e)
        {
            serialPort1.PortName = COM_ports_box.Text;
        }

        private void SetSerialSettings()
        {
            serialPort1.PortName = COM_ports_box.Text;
            serialPort1.BaudRate = 9600;
            serialPort1.DataBits = 8;
            serialPort1.Parity = Parity.None;
            serialPort1.StopBits = StopBits.One;
        }

        private void getPortNames()
        {
            foreach (string s in SerialPort.GetPortNames())
            {
                serialPorts = s;
                if (serialPorts != s)
                {
                    COM_ports_box.Items.Add(s);
                }
            }
        }
               
        private void load_button_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }
        
        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            //textFromFile;
            StreamReader streamReader = new StreamReader(openFileDialog1.FileName);
            textFromFile = streamReader.ReadToEnd();
            Current_cfg_box.Text = textFromFile;
        }

        private void newConfig_button_Click(object sender, EventArgs e)
        {
            var newwindow = new newConfig();
            newwindow.Show();
        }

        private void Restart_button_Click(object sender, EventArgs e)
        {
            switch (MessageBox.Show("Are you sure you want to restart the system? ", "Warning!", MessageBoxButtons.YesNo,
                            //MessageBoxIcon.Warning // for Warning  
                            //MessageBoxIcon.Error // for Error 
                            //MessageBoxIcon.Information  // for Information
                            MessageBoxIcon.Question // for Question
                            ))
            {
                case DialogResult.Yes: RestartSystem(); break;
                case DialogResult.No: break;
            }            
        }
                
        private void RestartSystem()
        {
            MessageBox.Show("Restarting the system!");
        }

        private void NewUserButton_Click(object sender, EventArgs e)
        {
            var newwindow = new NewUser();
            newwindow.Show();
        }

        private void onButton_Click(object sender, EventArgs e)
        {

            progressLED.Value = 100;
            Online_offline_label.Text = "Online!";
                
         }

        private void offButton_Click(object sender, EventArgs e)
        {
            progressLED.Value = 0;
            Online_offline_label.Text = "Offline/Disconnected!";
        }

        private void LogOutButton_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            this.Close();
            var newwindow = new Login_form();
            newwindow.Show();

        }
    }
}
    