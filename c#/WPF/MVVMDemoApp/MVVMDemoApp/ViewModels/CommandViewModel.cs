namespace MVVMDemoApp.ViewModels
{
    using System;
    using System.Windows.Input;

    class CommandViewModel : ViewModelBase
    {
        public CommandViewModel(string displayName, ICommand command)
        {
            if (command == null)
                throw new ArgumentNullException(nameof(command));

            DisplayName = displayName;
            Command = command;
        }

        public ICommand Command
        {
            get;
            private set;
        }
    }
}
