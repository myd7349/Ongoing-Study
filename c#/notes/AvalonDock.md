[AvalonDock](https://github.com/xceedsoftware/wpftoolkit/wiki/AvalonDock)

[AvalonDock](https://github.com/Dirkster99/AvalonDock)

[AvalonDock [2.0] Tutorial Part 1 - Adding a Tool Window](https://www.codeproject.com/Articles/483507/AvalonDock-Tutorial-Part-Adding-a-Tool-Windo)

[AvalonDock [2.0] Tutorial Part 2 - Adding a Start Page](https://www.codeproject.com/Articles/483533/AvalonDock-Tutorial-Part-Adding-a-Start-Page)

[AvalonDock [2.0] Tutorial Part 3 - AvalonEdit in AvalonDock](https://www.codeproject.com/Articles/570313/AvalonDock-Tutorial-Part-AvalonEdit-in-Avalo)

[AvalonDock [2.0] Tutorial Part 4 - Integrating AvalonEdit Options](https://www.codeproject.com/Articles/570324/AvalonDock-Tutorial-Part-Integrating-AvalonE)

[AvalonDock [2.0] Tutorial Part 5 - Load/Save Layout with De-Referenced DockingManager](https://www.codeproject.com/Articles/719143/AvalonDock-Tutorial-Part-Load-Save-Layout)

[AvalonDock 2.0 and MVVM](https://www.lostindetails.com/articles/avalondock-2.0-with-mvvm)

[AvalonDockMVVM](https://github.com/8/AvalonDockMVVM)

Question: How to change the default padding of LayoutDocumentPaneControl?

Answer:

```csharp
public class LayoutInitializer : ILayoutUpdateStrategy
{
    public bool BeforeInsertDocument(LayoutRoot layout, LayoutDocument documentToShow, ILayoutContainer destinationContainer)
    {
        var destPane = destinationContainer as LayoutDocumentPane;
        if (destPane == null)
            return false;

        var destPaneControl = destinationContainer.FindParent<LayoutDocumentPaneControl>();

        return false;
    }
}
```

[Prevent docking AvalonDock](https://stackoverflow.com/questions/29734346/prevent-docking-avalondock)

[Remove AvalonDock dock and close buttons](https://stackoverflow.com/questions/11987893/remove-avalondock-dock-and-close-buttons)

[AvalonDock DocumentPane not restoring correctly](https://stackoverflow.com/questions/13314227/avalondock-documentpane-not-restoring-correctly)

[WPF实现选项卡效果（1）——使用AvalonDock](https://blog.csdn.net/honantic/article/details/45965965)

[WPF实现选项卡效果（2）——动态添加AvalonDock选项卡](https://blog.csdn.net/honantic/article/details/45966547)

[WPF实现选项卡效果（3）——自定义动态添加的AvalonDock选项卡内容](https://blog.csdn.net/honantic/article/details/45967319)

[AvalonDock](https://github.com/honantic/AvalonDock)

[In the Avalon Dock, How to hide LayoutDocumentPane item programatically and also restore them](https://stackoverflow.com/questions/52869506/in-the-avalon-dock-how-to-hide-layoutdocumentpane-item-programatically-and-also)

[LayoutDocument hide header tabs in DockingManager.DocumentPaneControlStyle](https://stackoverflow.com/questions/35405482/layoutdocument-hide-header-tabs-in-dockingmanager-documentpanecontrolstyle)

[AvalonDock - prevent anchorable pane docking in document pane](https://stackoverflow.com/questions/25444721/avalondock-prevent-anchorable-pane-docking-in-document-pane)

[AvalonDock 2.0 Floating Window looses maximized state on MainWindow minimize / restore](https://stackoverflow.com/questions/25963908/avalondock-2-0-floating-window-looses-maximized-state-on-mainwindow-minimize-r)

https://github.com/Dirkster99/AvalonDock/blob/master/source/MLibTest/MLibTest/Demos/LayoutInitializer.cs

[Saving window layouts](https://github.com/Dirkster99/AvalonDock/issues/353)

[AvalonDock [2.0] Tutorial Part 5 - Load/Save Layout with De-Referenced DockingManager](https://www.codeproject.com/Articles/719143/AvalonDock-Tutorial-Part-Load-Save-Layout)

[Layout "locking" method for Anchorables (tool windows)](https://github.com/Dirkster99/AvalonDock/issues/136)

[How to collapse or hide Anchorable on loading](https://github.com/Dirkster99/AvalonDock/issues/145)

> The Layout serializing/deserializing methods are implemented to support storing and restoring previously used layouts. You can use the LayoutSerializationCallback to indicate whether a part of the layout should not be reloaded or not.

[AvalonDock 2.0 increasing grip size](https://stackoverflow.com/questions/31571769/avalondock-2-0-increasing-grip-size)

> GridSplitterWidth="10"

[How do I move the AvalonDock Anchorable Pane tab to the top instead of the bottom?](https://stackoverflow.com/questions/29434424/how-do-i-move-the-avalondock-anchorable-pane-tab-to-the-top-instead-of-the-botto)

[Why do AvalonDock panes collapse in height when splitters first moved?](https://stackoverflow.com/questions/65523662/why-do-avalondock-panes-collapse-in-height-when-splitters-first-moved)

[how to set width for Avalondock LayoutAnchorablePane](https://stackoverflow.com/questions/32080027/how-to-set-width-for-avalondock-layoutanchorablepane)
