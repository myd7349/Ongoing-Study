namespace PlayWaveFileDemo
{
    using System.Windows.Forms;

    using NAudio.Wave;

    public partial class PropertiesForm : Form
    {
        public PropertiesForm(WaveFormat waveFormat)
        {
            InitializeComponent();

            propertyGrid_.SelectedObject = waveFormat;
        }
    }
}
