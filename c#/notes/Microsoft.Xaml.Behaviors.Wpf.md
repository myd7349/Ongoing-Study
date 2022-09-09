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

- [How to prevent InvokeCommandAction from propagating event to parent elements?](https://stackoverflow.com/questions/7647625/how-to-prevent-invokecommandaction-from-propagating-event-to-parent-elements)

  ```csharp
  using System;

  using Microsoft.Xaml.Behaviors;

  public class HandlingEventTrigger : EventTrigger
  {
      protected override void OnEvent(EventArgs eventArgs)
      {
          var routedEventArgs = eventArgs as System.Windows.RoutedEventArgs;
          if (routedEventArgs != null)
              routedEventArgs.Handled = true;

          base.OnEvent(eventArgs);
      }
  }
  ```

[Passing event args and sender to the RelayCommand](https://stackoverflow.com/questions/2963830/passing-event-args-and-sender-to-the-relaycommand)

[How to Pass PassEventArgsToCommand along with CommandParameter in Interaction.Triggers](https://stackoverflow.com/questions/34919571/how-to-pass-passeventargstocommand-along-with-commandparameter-in-interaction-tr)

Triggers:

- [MVVM pattern and dialogs](https://www.plainionist.net/Mvvm-Dialogs/)

ClearFocusOnClickBehavior:

- https://github.com/PixiEditor/PixiEditor/blob/master/src/PixiEditor/Views/Dialogs/SettingsWindow.xaml

- [WPF - Remove focus when clicking outside of a textbox](https://stackoverflow.com/questions/6489032/wpf-remove-focus-when-clicking-outside-of-a-textbox)

Interaction.Behaviors

- [In WPF, MVVM, How to set the Rows Selected from the View Model.](https://social.msdn.microsoft.com/Forums/vstudio/en-US/cc5976d9-f117-4acb-9943-b7f16fa79d0c/in-wpf-mvvm-how-to-set-the-rows-selected-from-the-view-model?forum=wpf)

- [Using behaviours to bind to read-only properties in MVVM](https://blog.magnusmontin.net/2014/01/30/wpf-using-behaviours-to-bind-to-readonly-properties-in-mvvm/)

[CallMethodAction](https://github.com/microsoft/XamlBehaviorsWpf/wiki/CallMethodAction)

- [How to set selected item of a DataGrid programmatically in WPF with MVVM application?](https://stackoverflow.com/questions/15826142/how-to-set-selected-item-of-a-datagrid-programmatically-in-wpf-with-mvvm-applica)

Issues:

- https://github.com/Statical/issue-load-microsoft-xaml-behaviors-wpf
