<Query Kind="Program">
  <Namespace>System.Data.Linq</Namespace>
  <Namespace>System.Linq</Namespace>
</Query>

void Main()
{
    var data = new Int16[] { 1, 2, 3, 4 };
    var bytes = new byte[data.Length * sizeof(Int16)];
    Buffer.BlockCopy(data, 0, bytes, 0, bytes.Length);
    Console.WriteLine(bytes);
    
    var bytes2 = data.Select(i => BitConverter.GetBytes(i)).ToArray();
    Console.WriteLine(bytes2);
    
    var bin = new Binary(bytes);
    Console.WriteLine(bin);
    Console.WriteLine(bin.Equals(bytes));
}

// References:
// https://stackoverflow.com/questions/1318933/c-sharp-int-to-byte
// https://www.codeproject.com/questions/1029903/convert-an-integer-array-to-a-byte-array
// https://stackoverflow.com/questions/18472867/checking-equality-for-two-byte-arrays
// https://stackoverflow.com/questions/1547252/how-do-i-concatenate-two-arrays-in-c
