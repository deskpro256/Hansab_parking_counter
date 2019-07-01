using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Hansab_slave_configurator
{
    public partial class newConfig : Form
    {
        int numericValue;
        String textToFile = "Configuration of : \n";
        System.IO.StreamWriter sr;

        public newConfig()
        {
            InitializeComponent();
            SaveButton.Enabled = false;

        }

        private void Next_button_Click(object sender, EventArgs e)
        {
            numericValue = Convert.ToInt32(numericUpDown1.Value);
            generateNewGroupBox(numericValue);
        }

        private void generateNewGroupBox(int count)
        {
            for (int i = 0; i <= count; i++)
            {
                textToFile +="ID" + i + ", floor_id, 01, type, 1, maxCount, 250 \n";
            }
        }

        private void SaveButton_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
            sr = new System.IO.StreamWriter("..\\Desktop");
            sr.Close();
            // save config
            // send config to slaves
        }

        private void ApplyConfigSettingsButton_Click(object sender, EventArgs e)
        {
            testTextBox.AppendText(textToFile);
            testTextBox.AppendText(LotNameLocationBox.Text);
            testTextBox.AppendText("\n");
            SaveButton.Enabled = true;
        }

        private void CheckButton_Click(object sender, EventArgs e)
        {
            // chekck for correct inputs
            // if all good, enable apply button
            // else redo the shizz
        }
    }
}
