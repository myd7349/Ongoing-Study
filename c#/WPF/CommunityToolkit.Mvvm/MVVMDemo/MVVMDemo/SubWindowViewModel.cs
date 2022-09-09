using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MvvmDialogs;

namespace MVVMDemo
{
    internal class SubWindowViewModel : ObservableObject, IModalDialogViewModel
    {
        public SubWindowViewModel(string? text)
        {
            _text = text;

            OKCommand = new RelayCommand(OK);
            CancelCommand = new RelayCommand(Cancel);
        }

        public string? Text
        {
            get => _text;
            set => SetProperty(ref _text, value);
        }

        public IRelayCommand OKCommand { get; }

        public IRelayCommand CancelCommand { get; }

        public bool? DialogResult
        {
            get => _dialogResult;
            set => SetProperty(ref _dialogResult, value);
        }

        private void OK()
        {
            DialogResult = true;
        }

        private void Cancel()
        {
            DialogResult = false;
        }

        private string? _text;
        private bool? _dialogResult;
    }
}
