### Save & Restore Window Placement State

- [Save Window Placement State Sample](https://learn.microsoft.com/en-us/samples/microsoft/wpf-samples/save-window-placement-state-sample/)

  - https://github.com/microsoft/wpf-samples/tree/main/Windows/SaveWindowState

- [.NET WPF Remember window size between sessions](https://stackoverflow.com/questions/847752/net-wpf-remember-window-size-between-sessions)

- [Save and Restore WPF Window Size, Position, and/or State](https://www.codeproject.com/Articles/50761/Save-and-Restore-WPF-Window-Size-Position-and-or-S)

- [Jot](https://github.com/anakic/jot)

  - [WPF: How are you supposed to save window position in the year 2020?](https://www.reddit.com/r/csharp/comments/j0kkki/wpf_how_are_you_supposed_to_save_window_position/)

  - [Easier .NET settings](https://www.codeproject.com/Articles/475498/Easier-NET-settings)

### UIPropertyMetadata

- [UIPropertyMetadata Class](https://learn.microsoft.com/en-us/dotnet/api/system.windows.uipropertymetadata)

- [Where is Button.DialogResult in WPF?](https://stackoverflow.com/questions/1759372/where-is-button-dialogresult-in-wpf)

### Closed & Unloaded

- [Why does unloaded event of window do not fire in WPF?](https://stackoverflow.com/questions/8908276/why-does-unloaded-event-of-window-do-not-fire-in-wpf)

### InvalidateVisual

- [UIElement.InvalidateVisual](https://learn.microsoft.com/en-us/dotnet/api/system.windows.uielement.invalidatevisual?view=windowsdesktop-6.0)

- :star: [Deep Dive into WPF Layouting and Rendering](https://www.codeproject.com/Articles/5324971/Deep-Dive-into-WPF-Layouting-and-Rendering)

- [Understanding MeasureOverride and ArrangeOverride](https://www.codeproject.com/Articles/1034445/Understanding-MeasureOverride-and-ArrangeOverride)

- :star: [How can I manually tell an owner-drawn WPF Control to refresh/redraw without executing measure or arrange passes?](https://stackoverflow.com/questions/7801680/how-can-i-manually-tell-an-owner-drawn-wpf-control-to-refresh-redraw-without-exe)

  > Unfortunately, you must call InvalidateVisual, which calls InvalidateArrange internally. The OnRender method is called as part of the arrange phase, so you need to tell WPF to rearrange the control (which InvalidateArrange does) and that it needs to redraw (which InvalidateVisual does). 
  >
  > The FrameworkPropertyMetadata.AffectsRender option simply tells WPF to call InvalidateVisual when the associated property changes.

- [Render WPF UIElement without using arrange()](https://stackoverflow.com/questions/47524081/render-wpf-uielement-without-using-arrange)

- [WPF OnRender not called on FrameworkElement](https://stackoverflow.com/questions/64207715/wpf-onrender-not-called-on-frameworkelement)

- [Force a repaint of a custom drawn UIElement in a custom WPF control](https://stackoverflow.com/questions/40804751/force-a-repaint-of-a-custom-drawn-uielement-in-a-custom-wpf-control)


