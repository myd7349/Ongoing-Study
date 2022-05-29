[WPF how to bind mousedown (command/action) to label](https://stackoverflow.com/questions/47199489/wpf-how-to-bind-mousedown-command-action-to-label)

[Putting things together](https://learn.microsoft.com/en-us/windows/communitytoolkit/mvvm/puttingthingstogether?source=recommendations)

EventTrigger:

- https://github.com/FantasticFiasco/mvvm-dialogs/blob/v8.0.0/samples/net-framework/Demo.ActivateNonModalDialog/CurrentTimeDialog.xaml

- [MVVM Passing EventArgs As Command Parameter](https://stackoverflow.com/questions/6205472/mvvm-passing-eventargs-as-command-parameter)

  ```
   <i:Interaction.Triggers>
      <i:EventTrigger EventName="Navigated">
          <cmd:EventToCommand Command="{Binding NavigatedEvent}"
                              PassEventArgsToCommand="True" />
      </i:EventTrigger>
  </i:Interaction.Triggers>
  ```

- [How to prevent InvokeCommandAction from propagating event to parent elements?](https://stackoverflow.com/questions/7647625/how-to-prevent-invokecommandaction-from-propagating-event-to-parent-elements)

- [Binding Events to Commands](https://prismlibrary.com/docs/wpf/interactivity/event-to-command.html)

- [WPF Event Passing Between two child usercontrol of a main usercontrol](https://stackoverflow.com/questions/6302321/wpf-event-passing-between-two-child-usercontrol-of-a-main-usercontrol)

- [How do I use EventToCommand to handle routed event from a child control of a WPF panel?](https://stackoverflow.com/questions/19686304/how-do-i-use-eventtocommand-to-handle-routed-event-from-a-child-control-of-a-wpf)

  - EventToCommand

- [MVVM - Commands, RelayCommands and EventToCommand](https://learn.microsoft.com/en-us/archive/msdn-magazine/2013/may/mvvm-commands-relaycommands-and-eventtocommand)

- [EventTrigger on UserControl 'Loaded' not calling ICommand.Execute](https://stackoverflow.com/questions/66444407/eventtrigger-on-usercontrol-loaded-not-calling-icommand-execute)

- [Interaction Triggers in Style in ResourceDictionary WPF](https://stackoverflow.com/questions/22321966/interaction-triggers-in-style-in-resourcedictionary-wpf)

- [How to prevent InvokeCommandAction from propagating event to parent elements?](https://stackoverflow.com/questions/7647625/how-to-prevent-invokecommandaction-from-propagating-event-to-parent-elements)

- [How to bind a custom routed event to the view model in a MVVM pattern?](https://learn.microsoft.com/en-us/answers/questions/797148/how-to-bind-a-custom-routed-event-to-the-view-mode.html)

Triggers:

- [MVVM pattern and dialogs](https://www.plainionist.net/Mvvm-Dialogs/)
