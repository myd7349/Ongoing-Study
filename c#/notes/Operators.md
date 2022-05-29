##### Null-coalescing assignment

C# 10.0 in a Nutshell

> The ??= operator assigns a variable only if it’s null.

[?? and ??= operators (C# reference)](https://learn.microsoft.com/en-us/dotnet/csharp/language-reference/operators/null-coalescing-operator)

https://github.com/mono/SkiaSharp/blob/v2.80.3/binding/Binding/SkiaApi.generated.cs

The old way:

```csharp
public RelayCommand MyCommand =>
    myCommand_ ??
    (myCommand_ = new RelayCommand(OnMyCommand));
```

##### =

https://learn.microsoft.com/en-us/dotnet/core/extensions/dependency-injection-usage

```csharp
public OperationLogger(
    ITransientOperation transientOperation,
    IScopedOperation scopedOperation,
    ISingletonOperation singletonOperation) =>
    (_transientOperation, _scopedOperation, _singletonOperation) =
        (transientOperation, scopedOperation, singletonOperation);
```
