namespace ScriptPlayground
{
    using System;
    using System.Drawing;
    using System.Drawing.Imaging;
    using System.Windows.Forms;

    using Faker;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private void nameCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            nameTextBox_.Enabled = nameCheckBox_.Checked;
        }

        private void ageCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            ageTextBox_.Enabled = ageCheckBox_.Checked;
        }

        private void genderCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            genderComboBox_.Enabled = genderCheckBox_.Checked;
        }

        private void idCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            idTextBox_.Enabled = idCheckBox_.Checked;
        }

        private void addressCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            addressTextBox_.Enabled = addressCheckBox_.Checked;

            if (addressTextBox_.Enabled && addressTextBox_.Text == string.Empty)
                addressTextBox_.Text = Address.StreetAddress();
        }

        private void phoneCheckBox__CheckedChanged(object sender, EventArgs e)
        {
            phoneTextBox_.Enabled = phoneCheckBox_.Checked;

            if (phoneTextBox_.Enabled && phoneTextBox_.Text == string.Empty)
                phoneTextBox_.Text = Phone.Number();
        }

        private void previewButton__Click(object sender, EventArgs e)
        {
            ReportUtility.CreateReport(GetPerson());

            using (var report = new Metafile("Report.emf"))
            using (var previewForm = new PreviewForm(report))
            {
                previewForm.ShowDialog();
            }
        }

        private Person GetPerson()
        {
            Person person = new Person();

            if (nameTextBox_.Enabled)
                person.Name = nameTextBox_.Text;

            if (ageTextBox_.Enabled)
            {
                int age;
                if (int.TryParse(ageTextBox_.Text, out age))
                    person.Age = age;
            }

            if (genderComboBox_.Enabled)
                person.Gender = genderComboBox_.SelectedItem.ToString();

            if (idTextBox_.Enabled)
                person.ID = idTextBox_.Text;

            if (addressTextBox_.Enabled)
                person.Address = addressTextBox_.Text;

            if (phoneTextBox_.Enabled)
                person.Phone = phoneTextBox_.Text;

            return person;
        }
    }
}
