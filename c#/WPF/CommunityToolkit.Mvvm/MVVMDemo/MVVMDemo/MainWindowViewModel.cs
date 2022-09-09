using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MvvmDialogs;
using MvvmDialogs.FrameworkDialogs.OpenFile;

namespace MVVMDemo
{
    internal class MainWindowViewModel : ObservableObject
    {
        public MainWindowViewModel()
        {
            _dialogService = new DialogService();

            LoadedCommand = new RelayCommand(Load);
            ClosedCommand = new RelayCommand(Close);
            ShowTextCommand = new RelayCommand(ShowText, () => !string.IsNullOrEmpty(Text));
            OpenFileCommand = new RelayCommand(OpenFile);
            EditTextCommand = new RelayCommand(EditText);
        }

        public string? Text
        {
            get => _text;

            set
            {
                if (SetProperty(ref _text, value))
                    ShowTextCommand.NotifyCanExecuteChanged();
            }
        }

        public IRelayCommand LoadedCommand { get; }

        public IRelayCommand ClosedCommand { get; }

        public IRelayCommand ShowTextCommand { get; }

        public IRelayCommand OpenFileCommand { get; }

        public IRelayCommand EditTextCommand { get; }

        private void Load()
        {
            Text = "Hello!";
        }

        private void Close()
        {
        }

        private void ShowText()
        {
            _dialogService.ShowMessageBox(this, _text ?? string.Empty);
        }

        private void OpenFile()
        {
            var openFileDialogSettings = new OpenFileDialogSettings();
            if (_dialogService.ShowOpenFileDialog(this, openFileDialogSettings) == true)
                _dialogService.ShowMessageBox(this, openFileDialogSettings.FileName);
        }

        private void EditText()
        {
            var subWindowViewModel = new SubWindowViewModel(Text);
            if (_dialogService.ShowDialog(this, subWindowViewModel) == true)
                Text = subWindowViewModel.Text;
        }

        private IDialogService _dialogService;
        private string? _text;
    }
}
