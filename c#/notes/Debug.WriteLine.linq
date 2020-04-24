<Query Kind="Statements" />

var numbers = new string[] { "I", "II", "III", "IV", "V" };
Console.WriteLine("!!! Numbers: {0}", string.Join(", ", numbers));
Debug.WriteLine("!!! Numbers: {0}", string.Join(", ", numbers));
Debug.WriteLine("!!! Numbers: ", string.Join(", ", numbers));
Debug.WriteLine("!!! Numbers: {0}", (object)string.Join(", ", numbers));

// References:
// [Calling Console.WriteLine from multiple threads](https://stackoverflow.com/questions/1079980/calling-console-writeline-from-multiple-threads)
// [What's the difference between Console.WriteLine() vs Debug.WriteLine()?](https://stackoverflow.com/questions/3012822/whats-the-difference-between-console-writeline-vs-debug-writeline)

/*
Output:
!!! Numbers: I, II, III, IV, V
I, II, III, IV, V: !!! Numbers: {0}
I, II, III, IV, V: !!! Numbers: 
!!! Numbers: I, II, III, IV, V
*/