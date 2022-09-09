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
// [how to get both fields and properties in single call via reflection?] (https://stackoverflow.com/questions/12680341/how-to-get-both-fields-and-properties-in-single-call-via-reflection)
// [Deep Copy using Reflection in an Extension Method for Silverlight?](https://stackoverflow.com/questions/13198658/deep-copy-using-reflection-in-an-extension-method-for-silverlight)
// https://github.com/force-net/DeepCloner
// https://github.com/ReubenBond/DeepCopy
// https://github.com/AlenToma/FastDeepCloner
// https://github.com/mijay/NClone
// https://github.com/junweilee/Nuclex.Cloning
// [Fastest Way to do Shallow Copy in C#](https://stackoverflow.com/questions/966451/fastest-way-to-do-shallow-copy-in-c-sharp)
// [C# Object Clone Wars](https://www.csharp411.com/c-object-clone-wars/)
// [5 Ways to Clone An Object in C#](https://levelup.gitconnected.com/5-ways-to-clone-an-object-in-c-d1374ec28efa)
// [Why Copying an Object is a terrible thing to do?](http://agiledeveloper.com/articles/cloning072002.htm)
// https://gist.github.com/cristi993/fe4ade633fcc304f4040
// [Fast Deep Copy by Expression Trees (C#)](https://www.codeproject.com/Articles/1111658/Fast-Deep-Copy-by-Expression-Trees-C-Sharp)
// https://github.com/lsadam0/FastClone.Fody
// https://github.com/adrianaxente/FastCloner
// [C#几种深拷贝方法探究及性能比较](https://www.cnblogs.com/SF8588/p/16152078.html)
