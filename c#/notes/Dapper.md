### Articles

[How do you bind Dapper query result to WPF DataGrid](https://stackoverflow.com/questions/13299425/how-do-you-bind-dapper-query-result-to-wpf-datagrid)

[Delete multiple objects with a single query (or in transaction)](https://stackoverflow.com/questions/52588892/delete-multiple-objects-with-a-single-query-or-in-transaction)

[How to use transactions with dapper.net?](https://stackoverflow.com/questions/10363933/how-to-use-transactions-with-dapper-net)

[Bulk inserts taking longer than expected using Dapper](https://stackoverflow.com/questions/10689779/bulk-inserts-taking-longer-than-expected-using-dapper)

[Using Async Await keywords with Dapper](https://stackoverflow.com/questions/25833426/using-async-await-keywords-with-dapper)

[Selecting Single Rows Of Data With Dapper](https://www.learndapper.com/selecting-single-rows)

```csharp
using (var connection = new SqlConnection(connString))
{
    var sql = "select ProductId, Productname from Products where Discontinued = 1";
    var products = connection.Query<Product>(sql);
    foreach (var product in products)
    {
        Console.WriteLine($"{product.ProductId} {product.ProductName}: {product.Discontinued}");
    }
    Console.ReadLine();
}
```

### YouTube Videos

[Using SQLite in C# - Building Simple, Powerful, Portable Databases for Your Application](https://www.youtube.com/watch?v=ayp3tHEkRc0)

[Introduction to Dapper, using WPF forms. (v2)](https://www.youtube.com/watch?v=lkDdMkSv-tU)

### [Dapper-Extensions](https://github.com/tmsmith/Dapper-Extensions)

```csharp
class Person
{
    public string Name { get; set; }
};

var predicate = Predicates.Field<Person>(
    p => p.Name, Operator.Like, "Wang%");
var wang = connection.GetList<Person>(predicate,
    new [] { Predicates.Sort<Person>("Name", true) }); // OK
```


```csharp
class Person
{
    public string Name;
};

var predicate = Predicates.Field<Person>(
    p => p.Name, Operator.Like, "Wang%");
var wang = connection.GetList<Person>(predicate,
    new [] { Predicates.Sort<Person>("Name", true) }); // Not OK
```

### [Dapper.SimpleCRUD](https://github.com/ericdc1/Dapper.SimpleCRUD)

[Delete a List<T> using Dapper](https://stackoverflow.com/questions/45971254/delete-a-listt-using-dapper)

### Bulk delete

[Bulk Deleting Data With Dapper](https://www.learndapper.com/bulk-operations/bulk-delete)

[Correct method of deleting over 2100 rows (by ID) with Dapper](https://stackoverflow.com/questions/9946287/correct-method-of-deleting-over-2100-rows-by-id-with-dapper)
