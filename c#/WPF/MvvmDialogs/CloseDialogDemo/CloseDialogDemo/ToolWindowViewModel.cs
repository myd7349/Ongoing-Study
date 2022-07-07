using System.ComponentModel;

using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MvvmDialogs;

namespace CloseDialogDemo
{
    public class ToolWindowViewModel : ObservableObject, IModalDialogViewModel
    {
        public ToolWindowViewModel(IDialogService dialogService)
        {
            dialogService_ = dialogService;
        }

        public IRelayCommand CloseCommand =>
            closeCommand_ ??
            (closeCommand_ = new RelayCommand(Close));

        public bool? DialogResult
        {
            get => dialogResult_;
            set => SetProperty(ref dialogResult_, value);
        }

        protected override void OnPropertyChanged(PropertyChangedEventArgs e)
        {
            // Be careful when overriding OnPropertyChanged, if you
            // forget this line below, then data binding won't work
            // as expected.
            // You can give this a try by comment out this line.
            base.OnPropertyChanged(e);

            //if (e.PropertyName == nameof(DialogResult))
            //    dialogService_.Close(this);
        }
        
        private void Close()
        {
            DialogResult = true;
        }

        private IRelayCommand closeCommand_ = null!;
        private readonly IDialogService dialogService_ = null!;
        private bool? dialogResult_;
    }
}
