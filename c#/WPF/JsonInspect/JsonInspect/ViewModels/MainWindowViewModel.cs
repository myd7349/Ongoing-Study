using Prism.Mvvm;

namespace JsonInspect.ViewModels
{
    public class MainWindowViewModel : BindableBase
    {
        public string Title
        {
            get
            {
                if (string.IsNullOrEmpty(FilePath))
                    return "JsonInspect";
                else
                    return $"{FilePath} - JsonInspect";
            }
        }

        public string FilePath
        {
            get => filePath_;

            set
            {
                if (SetProperty(ref filePath_, value))
                    RaisePropertyChanged("Title");
            }
        }

        public bool? Indented
        {
            get => indented_;
            set => SetProperty(ref indented_, value);
        }

        public bool IsBson
        {
            get => isBson_;
            set => SetProperty(ref isBson_, value);
        }

        public bool WordWrap
        {
            get => wordWrap_;
            set => SetProperty(ref wordWrap_, value);
        }

        public string FontFamily
        {
            get => fontFamily_;
            set => SetProperty(ref fontFamily_, value);
        }

        private string filePath_;
        private bool? indented_;
        private bool isBson_;
        private bool wordWrap_;
        private string fontFamily_ = "Consolas";
    }
}
