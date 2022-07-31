using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Threading;

using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;

using Common.WPF;

namespace AsyncThread
{
    internal partial class MainWindowViewModel : ObservableObject
    {
        [ObservableProperty]
        private string? currentTime;

        [RelayCommand]
        private void StartTimer()
        {
            Debug.Assert(_timerThread == null);

            _running = true;

            _cancellationTokenSource = new CancellationTokenSource();

            _currentTimeLabel = Application.Current.MainWindow.FindChild<Label>("currentTimeLabel_");

            _timerThread = new Thread(TimerThreadCallback);
            _timerThread.Start();
        }

        [RelayCommand]
        private void StopTimer()
        {
            Debug.Assert(_timerThread != null);

            _running = false;

            _cancellationTokenSource!.Cancel();

            _timerThread.Join();
            _timerThread = null;

            _cancellationTokenSource = null;
        }

        private async void TimerThreadCallback()
        {
            while (_running)
            {
                await Task.Delay(1000);

                // Get current time in HH:mm:ss format.
                CurrentTime = DateTime.Now.ToString("HH:mm:ss");

                _context.Invoke(
                    async () =>
                    {
                        await Task.Delay(10);
                        _currentTimeLabel.Content = CurrentTime;
                    },
                    DispatcherPriority.Normal,
                    _cancellationTokenSource!.Token); // _cancellationTokenSource might be null here.
            }
        }

        private WPFContext _context = new WPFContext();
        private Thread? _timerThread;
        private CancellationTokenSource? _cancellationTokenSource;
        private bool _running;
        private Label _currentTimeLabel = null!;
    }
}


// References:
// [Behavior of async await with new threads](https://stackoverflow.com/questions/29151168/behavior-of-async-await-with-new-threads)
// [Thread.Join() method not working with nested async void.](https://github.com/dotnet/core/issues/3591)
// 
