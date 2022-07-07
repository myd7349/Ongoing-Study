using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MvvmDialogs;

namespace CloseDialogDemo
{
    public class MainWindowViewModel : ObservableObject
    {
        public IRelayCommand OpenDialogCommand =>
            openDialogCommand_ ??
            (openDialogCommand_ = new RelayCommand(OpenDialog));

        public IRelayCommand CloseDialogCommand =>
            closeDialogCommand_ ??
            (closeDialogCommand_ = new RelayCommand(CloseDialog));

        private void OpenDialog()
        {
            var subWindowViewModel = new SubWindowViewModel(dialogService_);
            dialogService_.ShowDialog(this, subWindowViewModel);
        }

        private void CloseDialog()
        {
#if false
            // This won't work:
            DialogResult = false;
#else
            dialogService_.Close(this);
#endif
        }

        private readonly IDialogService dialogService_ = new DialogService();
        private IRelayCommand openDialogCommand_ = null!;
        private IRelayCommand closeDialogCommand_ = null!;
    }
}
