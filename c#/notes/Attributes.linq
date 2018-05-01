<Query Kind="Program">
  <Reference>&lt;RuntimeDirectory&gt;\System.ComponentModel.DataAnnotations.dll</Reference>
  <Namespace>System.ComponentModel</Namespace>
  <Namespace>System.ComponentModel.DataAnnotations</Namespace>
</Query>

public class Person
{
    [DefaultValue(0)]
    [Range(0, 120, ErrorMessage = "Value for {0} must be between {1} and {2}.")]
    public int Age { get; set; }
}

void Main()
{
    // A DefaultValueAttribute will not cause a member to be automatically initialized 
    // with the attribute's value. You must set the initial value in your code.
    var person = new Person();
    Console.WriteLine(person.Age);
    
    person.Age = 999;
    Console.WriteLine(person.Age);
    
}

// References:
// https://msdn.microsoft.com/en-us/library/microsoft.visualstudio.testtools.unittesting.classinitializeattribute.aspx
// https://stackoverflow.com/questions/144833/most-useful-attributes
// https://msdn.microsoft.com/en-us/library/microsoft.visualstudio.testtools.unittesting.expectedexceptionattribute.aspx
// https://stackoverflow.com/questions/8817031/how-to-check-if-method-has-an-attribute
// https://stackoverflow.com/questions/7926693/validation-using-attributes
// https://msdn.microsoft.com/en-us/library/cc668224.aspx
// https://stackoverflow.com/questions/11959431/how-to-create-a-custom-validation-attribute

