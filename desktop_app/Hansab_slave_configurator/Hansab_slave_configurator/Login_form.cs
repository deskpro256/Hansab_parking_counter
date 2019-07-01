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
    public partial class Login_form : Form
    {
        public string admin = "admin";
        public string admin_password = "qwerty";
        public string guest = "guest";
        public string guest_password = "qwerty";
        public string typeAdmin = "admin";
        public string typeGuest = "guest";
        public string username;
        public string password;


        public Login_form()
        {
            InitializeComponent();
        }

        private void username_box_TextChanged(object sender, EventArgs e)
        {
            Incorrect_label.Visible = false;
            username = username_box.Text;
        }

        private void password_box_TextChanged(object sender, EventArgs e)
        {
            Incorrect_label.Visible = false;
            password = password_box.Text;
        }

        private void login_button_Click(object sender, EventArgs e)
        {

            //check for user admin/guest
            //if admin go to admin page
            //else if guest user go to simplified page

            if ((username == admin) && (password == admin_password))
            {
                this.Hide();
                var newwindow = new Main(typeAdmin);
                newwindow.Show();
            }

            else if ((username == guest) && (password == guest_password))
            {
                this.Hide();
                var newwindow = new Main(typeGuest);
                newwindow.Show();
            }

            else if ( (username != admin) || (username != guest) || (password != guest_password) || (password != admin_password) )
            {
                Incorrect_label.Visible = true;
            }
            
        }

        private void ForgotButton_Click(object sender, EventArgs e)
        {           
            var newwindow = new ForgotPass();
            newwindow.Show();
        }
    }
}
