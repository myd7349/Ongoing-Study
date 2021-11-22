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

