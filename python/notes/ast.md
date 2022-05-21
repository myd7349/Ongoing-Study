[Lists in ConfigParser](https://stackoverflow.com/questions/335695/lists-in-configparser)

```python
#[section]
#option=["item1","item2","item3"]

import ConfigParser
import ast

my_list = ast.literal_eval(config.get("section", "option"))
print(type(my_list))
print(my_list)
```
