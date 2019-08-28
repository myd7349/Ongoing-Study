<Query Kind="Statements" />

var anInt = 1;
var aBool = true;
var aString = "3";
var formated = string.Format("{0},{1},{2}", anInt, aBool, aString);
Console.WriteLine(formated);

Console.WriteLine($"{anInt},{aBool},{aString}");


// References:
// [What does $ mean before a string?](https://stackoverflow.com/questions/31014869/what-does-mean-before-a-string)
// [What's with the dollar sign ($“string”)](https://stackoverflow.com/questions/32878549/whats-with-the-dollar-sign-string)
