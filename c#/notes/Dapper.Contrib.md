[Dapper - have a different tablename than the name of your entity / class](https://peterdaugaardrasmussen.com/2018/02/26/dapper-set-name-of-table-to-something-other-than-table/)

```csharp
[Table ("emps")]
public class Employee
{
    public int Id { get; set; }
    public string Name { get; set; }
}

public class Employee
{
    [Key]
    public int EmployeeId { get; set; }
    public string Name { get; set; }
}
```
