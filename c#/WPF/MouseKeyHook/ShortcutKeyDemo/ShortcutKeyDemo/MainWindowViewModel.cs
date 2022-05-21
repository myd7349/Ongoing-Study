using System.Windows.Input;

using CommunityToolkit.Mvvm.ComponentModel;

namespace ShortcutKeyDemo
{
    public class MainWindowViewModel : ObservableObject
    {
        public KeyGesture SayHelloShortcut
        {
            get => sayHelloShortcut_;
            set => SetProperty(ref sayHelloShortcut_, value);
        }

        public KeyGesture MinimizeShortcut
        {
            get => minimizeShortcut_;
            set => SetProperty(ref minimizeShortcut_, value);
        }

        public KeyGesture RestoreShortcut
        {
            get => restoreShortcut_;
            set => SetProperty(ref restoreShortcut_, value);
        }

        public bool IsHooked
        {
            get => isHooked_;

            set
            {
                if (SetProperty(ref isHooked_, value))
                    OnPropertyChanged(nameof(HookButtonText));
            }
        }

        public string HookButtonText => isHooked_ ? "Unhook" : "Hook";

        private KeyGesture sayHelloShortcut_;
        private KeyGesture minimizeShortcut_;
        private KeyGesture restoreShortcut_;
        private bool isHooked_;
    }
}
