[Closing a form during a constructor](https://stackoverflow.com/questions/3067901/closing-a-form-during-a-constructor)

[How can I make the cursor turn to the wait cursor?](https://stackoverflow.com/questions/1568557/how-can-i-make-the-cursor-turn-to-the-wait-cursor)

[What's the difference between Invoke() and BeginInvoke()](https://stackoverflow.com/questions/229554/whats-the-difference-between-invoke-and-begininvoke)

[Avoiding the woes of Invoke/BeginInvoke in cross-thread WinForm event handling?](https://stackoverflow.com/questions/1364116/avoiding-the-woes-of-invoke-begininvoke-in-cross-thread-winform-event-handling)

[How do I make a textbox that only accepts numbers?](https://stackoverflow.com/questions/463299/how-do-i-make-a-textbox-that-only-accepts-numbers)

[What is the difference between User Control, Custom Control and Component?](https://stackoverflow.com/questions/1322451/what-is-the-difference-between-user-control-custom-control-and-component)

[Control vs UserControl in WinForms?](https://stackoverflow.com/questions/921278/control-vs-usercontrol-in-winforms)

[UserControl vs CustomControl in C#](https://stackoverflow.com/questions/15294974/usercontrol-vs-customcontrol-in-c-sharp)

[How could i display a Graph on WindowsForms?](https://stackoverflow.com/questions/38713649/how-could-i-display-a-graph-on-windowsforms)

Awesome WinForms projects:

- https://github.com/d2phap/ImageGlass

[How to add print dialog to the printpreviewdialog?](https://stackoverflow.com/questions/40236241/how-to-add-print-dialog-to-the-printpreviewdialog)

[Show Print Dialog before printing](https://stackoverflow.com/questions/15985909/show-print-dialog-before-printing)

[Is it possible to use ShowDialog without blocking all forms?](https://stackoverflow.com/questions/428494/is-it-possible-to-use-showdialog-without-blocking-all-forms)

[How to create a modeless dialog box within a C# console app](https://stackoverflow.com/questions/38549753/how-to-create-a-modeless-dialog-box-within-a-c-sharp-console-app)

[Call MessageBox from async thread with Form1 as parent](https://stackoverflow.com/questions/5349524/call-messagebox-from-async-thread-with-form1-as-parent)

[Message box from another thread](https://stackoverflow.com/questions/12949333/message-box-from-another-thread)

[What's the difference between Invoke() and BeginInvoke()](https://stackoverflow.com/questions/229554/whats-the-difference-between-invoke-and-begininvoke)

> `Control.Invoke`: Executes on the UI thread, but calling thread waits for completion before continuing.
>
> `Control.BeginInvoke`: Executes on the UI thread, and calling thread doesn't wait for completion.

[Preventing a dialog from closing in the button's click event handler](https://stackoverflow.com/questions/2499644/preventing-a-dialog-from-closing-in-the-buttons-click-event-handler)

> **However, it would be a better design/user experience to display the validation errors inline** (via highlighting the offending fields in some way, displaying tooltips, etc.) **and prevent the user from selecting the OK button in the first place.**

[Set form location c#](https://stackoverflow.com/questions/24016638/set-form-location-c-sharp)

[How can I stop a double click of the window title bar from maximizing a window of FormBorderStyle.FixedToolWindow?](https://stackoverflow.com/questions/9588540/how-can-i-stop-a-double-click-of-the-window-title-bar-from-maximizing-a-window-o)

> You could set the `MaximizeBox` property of the form to false.

[Dialog MessageBox sometimes hidden behind the main form](https://stackoverflow.com/questions/3467403/dialog-messagebox-sometimes-hidden-behind-the-main-form)

[**Threading in Windows Forms**](https://jonskeet.uk/csharp/threads/winforms.html)

> 1. Never invoke any method or property on a control created on another thread other than `Invoke`, `BeginInvoke`, `EndInvoke` or `CreateGraphics`, and `InvokeRequired`.
>
>    Each control is effectively bound to a thread which runs its message pump. If you try to access or change anything in the UI (for example changing the `Text` property) from a different thread, you run a risk of your program hanging or misbehaving in other ways. You may get away with it in some cases, but only by blind luck. Fortunately, the `Invoke`, `BeginInvoke` and `EndInvoke` methods have been provided so that you can ask the UI thread to call a method for you in a safe manner.
>
> 2. Never execute a long-running piece of code in the UI thread.
>
>    If your code is running in the UI thread, that means no other code is running in that thread. That means you won't receive events, your controls won't be repainted, etc. This is a very Bad Thing. You *can* execute long-running code and periodically call `Application.DoEvents()`, and this is              the natural thing for many VB programmers to wish to do - but I'd advise against it. It means you have to consider re-entrancy issues etc, which I believe are harder to diagnose and fix than "normal" threading problems. You have to judge when to call `DoEvents`, and you can't use anything which might block (network access, for instance) without risking an unresponsive UI. I believe there are message pumping issues in terms of COM objects as well, but I don't have details of them (and I frankly wouldn't understand them fully anyway).
>
> So, if you have a piece of long-running code which you need to execute, you need to create a new thread(or use a thread pool thread if you prefer) to execute it on, and make sure it doesn't directly try to update the UI with its results. The thread creation part is the same as any other threading problem, and we've addressed that before. The interesting bit is going the other way - invoking a method on the UI thread in order to update the UI.

[Can BeginInvoke interrupt code already running on the UI thread?](https://stackoverflow.com/questions/2048491/can-begininvoke-interrupt-code-already-running-on-the-ui-thread)

