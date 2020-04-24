<Query Kind="Program" />

enum MyColors
{
    Red,
    Green,
    Blue
}

void Main()
{
    Console.WriteLine(MyColors.Red);
    Console.WriteLine(MyColors.Red.ToString());
    
    string colorString = "Red";
    MyColors color = MyColors.Blue;
    if (Enum.TryParse(colorString, out color))
        Console.WriteLine(color);
}

// References:
// https://stackoverflow.com/questions/23563960/how-to-get-enum-value-by-string-or-int
// https://stackoverflow.com/questions/424366/string-representation-of-an-enum
