using System;
using System.Threading;

namespace Common
{
    public class TickTimer : PropertyChangedBase
    {
        public TickTimer()
            : this(1000)
        {
        }

        public TickTimer(int intervalInMs)
        {
            StartTime = DateTime.Now;
            timer_ = new Timer(Tick, null, 0, intervalInMs);
        }

        public DateTime StartTime { get; }

        public DateTime Now
        {
            get => now_;

            set
            {
                now_ = value;
                OnPropertyChanged();
            }
        }

        public TimeSpan ElapsedTime
        {
            get => elapsedTime_;

            set
            {
                elapsedTime_ = value;
                OnPropertyChanged();
            }
        }

        private void Tick(object state)
        {
            Now = DateTime.Now;
            ElapsedTime = Now - StartTime;
        }

        private Timer timer_;
        private DateTime now_;
        private TimeSpan elapsedTime_;
    }
}


// References:
// [WPF TextBox binding DateTime](https://stackoverflow.com/questions/27453733/wpf-textbox-binding-datetime)
// [WPF Countdown Timer Binding to different window](https://stackoverflow.com/questions/28272603/wpf-countdown-timer-binding-to-different-window)
// [Format TimeSpan greater than 24 hour](https://stackoverflow.com/questions/3505230/format-timespan-greater-than-24-hour)
// [C# convert int to string with padding zeros?](https://stackoverflow.com/questions/4325267/c-sharp-convert-int-to-string-with-padding-zeros)
// [Binding to DateTime.Now. Update the value](https://stackoverflow.com/questions/3354793/binding-to-datetime-now-update-the-value)
