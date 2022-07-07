using System.Drawing;

using CommunityToolkit.Mvvm.ComponentModel;
using MvvmDialogs;

namespace GetImageResolution
{
    internal class MainWindowViewModel : ObservableObject
    {
        public string? ImageFilePath
        {
            get => imageFilePath_;

            set
            {
                if (SetProperty(ref imageFilePath_, value))
                {
                    if (!string.IsNullOrEmpty(value))
                        Image = Image.FromFile(value);
                    else
                        Image = null;
                }
            }
        }

        public Image? Image
        {
            get => image_;
            set => SetProperty(ref image_, value);
        }

        private string? imageFilePath_;
        private Image? image_;
    }
}
