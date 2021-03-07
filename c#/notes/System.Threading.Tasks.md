[What is the use for Task.FromResult in C#](https://stackoverflow.com/questions/19568280/what-is-the-use-for-task-fromresulttresult-in-c-sharp)

[Task.FromResult应用场景举例](https://www.cnblogs.com/darrenji/p/4712504.html)

Note that:

```csharp
Task.Run(() => SomeSyncFunction());
```

can not be replaced with:

```csharp
Task.FromResult(SomeSyncFunction());
```

[Task.FromResult() vs. Task.Run()](https://stackoverflow.com/questions/34005397/task-fromresult-vs-task-run)

[Using Task.FromResult v/s await in C#](https://stackoverflow.com/questions/50726867/using-task-fromresult-v-s-await-in-c-sharp)

