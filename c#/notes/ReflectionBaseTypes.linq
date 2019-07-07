<Query Kind="Program">
  <Namespace>System.Reflection</Namespace>
</Query>

interface IFoo {}
interface IBar {}
interface IBarEx : IBar, IFoo {}

class Base : IBarEx {}
class Derived : Base {}


void Main()
{
    Console.WriteLine(typeof(IBarEx).BaseType);
    Console.WriteLine(typeof(IBarEx).GetInterfaces());
    
    Console.WriteLine("============================================================");
    
    Console.WriteLine(typeof(int).BaseType);
    Console.WriteLine(typeof(int).BaseType.BaseType);
    Console.WriteLine(typeof(int).BaseType.BaseType.BaseType);
    
    Console.WriteLine("============================================================");
    
    Console.WriteLine(typeof(Base).BaseType);
    Console.WriteLine(typeof(Base).GetInterfaces());
    Console.WriteLine(typeof(Base).GetInterface(typeof(IBar).FullName));
    Console.WriteLine(typeof(Base).GetInterface(typeof(IBarEx).FullName));
    Console.WriteLine(typeof(Base).GetInterface(nameof(IBar)));
    Console.WriteLine(typeof(Base).GetInterface(nameof(IBarEx)));
    
    Console.WriteLine("============================================================");

    Console.WriteLine(typeof(Derived).BaseType);
    Console.WriteLine(typeof(Derived).GetInterfaces());
    Console.WriteLine(typeof(Derived).GetInterface(nameof(IBar)));
}


// References:
// https://stackoverflow.com/questions/538541/how-to-get-interface-basetype-via-reflection
// https://stackoverflow.com/questions/8868119/find-all-parent-types-both-base-classes-and-interfaces
