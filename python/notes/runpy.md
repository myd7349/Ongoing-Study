https://github.com/microsoft/vcpkg/pull/24906

```python
import runpy

runpy.run_module("pip", run_name="__main__", alter_sys=True)
```
