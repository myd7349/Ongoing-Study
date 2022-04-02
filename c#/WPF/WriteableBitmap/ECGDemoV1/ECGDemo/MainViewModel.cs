using System;
using System.Windows.Input;
using System.Windows.Media;

using MvvmHelpers;
using MvvmHelpers.Commands;

using Common;

namespace ECGDemo
{
    class MainViewModel : BaseViewModel
    {
        static MainViewModel()
        {
            SpeedArray = new[]
            {
                "12.5mm/s",
                "25mm/s",
                "50mm/s",
            };

            AmplitudeArray = new[]
            {
                "5mm/mV",
                "10mm/mV",
                "20mm/mV",
            };
        }

        public MainViewModel(Action startAcquisition, Action stopAcquisition)
        {
            TickTimer = new TickTimer
            {
                Tick = false
            };

            startAcquisition_ = startAcquisition;
            stopAcquisition_ = stopAcquisition;

            StartOrStopCommand = new Command(StartOrStopAcquisition);
        }

        public TickTimer TickTimer { get; }

        public static readonly string[] SpeedArray;

        public static readonly string[] AmplitudeArray;

        public new bool IsBusy
        {
            get => base.IsBusy;

            set
            {
                base.IsBusy = value;
                OnPropertyChanged("ButtonImageUri");
            }
        }

        public string ButtonImageUri => IsBusy ? "Images/media-record.png" : "Images/go-next-8.png";

        public ICommand StartOrStopCommand { get; }

        public void StartOrStopAcquisition()
        {
            if (!IsBusy)
            {
                IsBusy = true;
                generator_ = new ECGenerator(heartRate_, samplingRate_);
                startAcquisition_?.Invoke();
                TickTimer.Tick = true;
            }
            else
            {
                stopAcquisition_?.Invoke();
                TickTimer.Tick = false;
                IsBusy = false;
            }
        }

        public double HR
        {
            get => heartRate_;
            set => SetProperty(ref heartRate_, value);
        }

        public int SamplingRate
        {
            get => samplingRate_;
            set => SetProperty(ref samplingRate_, value);
        }

        public ECGenerator ECGenerator
        {
            get => generator_;
        }

        public double Speed
        {
            get => speed_;
            set => SetProperty(ref speed_, value);
        }

        public double Amplitude
        {
            get => amplitude_;
            set => SetProperty(ref amplitude_, value);
        }

        public Color WaveColor
        {
            get => waveColor_;
            set => SetProperty(ref waveColor_, value);
        }

        public Color RefreshColor
        {
            get => refreshColor_;
            set => SetProperty(ref refreshColor_, value);
        }

        private double heartRate_ = 60;
        private int samplingRate_ = 500;
        private ECGenerator generator_;

        private Action startAcquisition_;
        private Action stopAcquisition_;

        private double speed_ = 25.0;
        private double amplitude_ = 10.0;

        private Color refreshColor_ = Colors.White;
        private Color waveColor_ = Colors.LightGreen;
    }
}


// References:
// [SkiaSharpFiddle](https://github.com/mattleibow/SkiaSharpFiddle)
