using System.Collections.ObjectModel;

using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using MvvmDialogs;

using Common;

namespace NetworkDemo
{
    internal class MainWindowViewModel : ObservableObject
    {
        public MainWindowViewModel()
        {
            GetIPAddresses();

            ParseEndPointCommand = new RelayCommand(
                ParseEndPoint, () => !string.IsNullOrEmpty(endPoint_));
            StartNCPACommand = new RelayCommand(NetworkHelper.StartNCPA);
        }
        
        public ObservableCollection<string> IPAddresses { get; }
            = new ObservableCollection<string>();

        public string? SelectedIPAddress
        {
            get => selectedIPAddress_;
            set => SetProperty(ref selectedIPAddress_, value);
        }

        public string? EndPoint
        {
            get => endPoint_;

            set
            {
                if (SetProperty(ref endPoint_, value))
                    ParseEndPointCommand.NotifyCanExecuteChanged();
            }
        }

        public IRelayCommand ParseEndPointCommand { get; }

        public IRelayCommand StartNCPACommand { get; }

        public string? ParsedResult
        {
            get => parsedResult_;
            set => SetProperty(ref parsedResult_, value);
        }

        private void GetIPAddresses()
        {
            IPAddresses.Clear();

            var selectedIPAddress = selectedIPAddress_;

            foreach (var address in NetworkHelper.GetIPAddresses())
            {
                var addressString = address.ToString();
                
                IPAddresses.Add(addressString);

                if (addressString == selectedIPAddress)
                    SelectedIPAddress = selectedIPAddress;
            }
        }

        private void ParseEndPoint()
        {
            var endPoint = NetworkHelper.ParseEndPoint(endPoint_);

            ParsedResult = $"IPAddress: {endPoint?.Address.ToString()}, Port: {endPoint?.Port}";
        }

        private IDialogService dialogService_ = Singleton<DialogService>.Instance;
        
        private string? selectedIPAddress_;
        private string? endPoint_;
        private string? parsedResult_;
    }
}
