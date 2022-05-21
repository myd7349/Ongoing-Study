namespace Common
{
    public class Ref<T> where T : struct
    {
        public Ref(T value) => Value = value;
    
        public T Value { get; set; }
    
        public static explicit operator Ref<T>(T value) => new(value);
    
        public static implicit operator T(Ref<T> value) => value.Value;
    
        public override string? ToString() => Value!.ToString(); // let fail and NullReferenceException
    }
}

/*
var tupleList = new List<Tuple<Window, bool>>();

foreach (var tuple in tupleList)
{
    bool canClose = false;
    // ...
    tuple.Item2 = canClose; // Boom!
}

var tupleList2 = new List<Tuple<Window, Ref<bool>>>();

foreach (var tuple in tupleList2)
{
    bool canClose = false;
    // ...
    tuple.Item2.Value = canClose; // Magic!
}
*/


// References:
// [C# - reference wrapper for value type](https://stackoverflow.com/questions/8735070/c-sharp-reference-wrapper-for-value-type)
// TupleExtension.cs
