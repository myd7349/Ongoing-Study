using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MvvmDialogs;

namespace CloseDialogDemo
{
    public class SubWindowViewModel : ObservableObject, IModalDialogViewModel
    {
        public SubWindowViewModel(IDialogService dialogService)
        {
            dialogService_ = dialogService;
        }

        public IRelayCommand OpenToolDialogCommand =>
            openToolDialogCommand_ ??
            (openToolDialogCommand_ = new RelayCommand(OpenToolDialog));

        public IRelayCommand CloseCommand =>
            closeCommand_ ??
            (closeCommand_ = new RelayCommand(Close));

        public bool? DialogResult
        {
            get => dialogResult_;
            set => SetProperty(ref dialogResult_, value);
        }

        private void OpenToolDialog()
        {
            var toolWindowViewModel = new ToolWindowViewModel(dialogService_);
            dialogService_.ShowDialog(this, toolWindowViewModel);
        }

        private void Close()
        {
            DialogResult = false;
        }

        private IRelayCommand openToolDialogCommand_ = null!;
        private IRelayCommand closeCommand_ = null!;
        private readonly IDialogService dialogService_ = null!;
        private bool? dialogResult_;
    }
}
