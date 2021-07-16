namespace ShowDialogAsync
{
    using System.Threading.Tasks;
    using System.Windows.Forms;

    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        private async Task<int> LoadDataAsync()
        {
            await Task.Delay(2000);
            return 42;
        }

        private async void loadDataButton__Click(object sender, System.EventArgs e)
        {
            var progressForm = new Form()
            {
                Width = 300,
                Height = 100,
                Text = "Please wait... "
            };

            object data;
            var progressFormTask = progressForm.ShowDialogAsync();
            try
            {
                data = await LoadDataAsync();
            }
            finally
            {
                progressForm.Close();
                await progressFormTask;
            }

            MessageBox.Show(data.ToString());
        }
    }
}


// References:
// [Async ShowDialog](https://stackoverflow.com/questions/33406939/async-showdialog)
