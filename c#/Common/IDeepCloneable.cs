namespace Common
{
    public interface IDeepCloneable
    {
        object DeepClone();
    }

    public interface IDeepCloneable<T> : IDeepCloneable
    {
        new T DeepClone();
    }
}

// References:
// [Proper way to implement ICloneable](https://stackoverflow.com/questions/21116554/proper-way-to-implement-icloneable)
// [Deep cloning objects](https://stackoverflow.com/questions/78536/deep-cloning-objects)
// [How do you do a deep copy of an object in .NET?](https://stackoverflow.com/questions/129389/how-do-you-do-a-deep-copy-of-an-object-in-net)
// https://github.com/ModernMAK/PartyClassCardGame/blob/main/Assets/Scripts/Core/IDeepCloneable.cs
// https://learn.microsoft.com/en-us/dotnet/api/system.object.memberwiseclone?view=net-6.0#system-object-memberwiseclone
