[How do you stop the Designer generating code for public properties on a User Control?](https://stackoverflow.com/questions/29696/how-do-you-stop-the-designer-generating-code-for-public-properties-on-a-user-con)
```csharp
[DesignerSerializationVisibility(DesignerSerializationVisibility.Hidden)]
public Background Background
{
    get;
    set;
}
```