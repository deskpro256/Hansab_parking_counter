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
    public partial class NewUser : Form
    {
        public NewUser()
        {
            InitializeComponent();
        }

        private void CreateButton_Click(object sender, EventArgs e)
        {
            MessageBox.Show("UserCreated", "aaaaaa", MessageBoxButtons.OK);
        }

        private void UsernameBox_TextChanged(object sender, EventArgs e)
        {

        }

        private void UserTypeBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void PasswordBox_TextChanged(object sender, EventArgs e)
        {

        }
    }
}
