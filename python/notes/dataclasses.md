https://github.com/shidenggui/pit/blob/main/git-objects.py

> ```python
> @dataclass
> class GitObject:
>     hash: str
>     type: str
>     length: int
>     content: bytes
> 
>     def display(self, mode: str, max_strlen: int = 88):
>         display = f"<{self.type.capitalize()}> {self.length} {self.hash}"
>         match (mode, self.type):
>             case ("full", "blob") if self.length > max_strlen:
>                 display += f" : {self.content[:max_strlen]}..."
>             case ("full", _):
>                 display += f" : {self.content}"
>             case _:
>                 pass
>         return display
> ```

[What are data classes and how are they different from common classes?](https://stackoverflow.com/questions/47955263/what-are-data-classes-and-how-are-they-different-from-common-classes)

[C-like structures in Python](https://stackoverflow.com/questions/35988/c-like-structures-in-python)

https://github.com/scipy/scipy/blob/main/scipy/spatial/distance.py
