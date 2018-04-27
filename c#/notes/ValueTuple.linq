<Query Kind="Statements" />

var valueTuple = new ValueTuple<int, int, int, int, int, int ,int, ValueTuple<int, int, int>>(1, 2, 3, 4, 5, 6, 7, new ValueTuple<int, int, int>(8, 9, 10));
Console.WriteLine(valueTuple.Item10);

// References:
// https://www.zhihu.com/question/274365296
// https://www.cnblogs.com/lavender000/p/6916157.html
