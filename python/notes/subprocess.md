##### Popen

https://github.com/angelpinheiro/mit2pdf/blob/fe8e7c6879c00b918c7784ce6b77e610f2c8d225/mit2pdf#L26-L34

```python
def run(cmd):
    """
    Runs a command and returns the result as a StrinIO file-like object
    """
    print "  Running $ " +  cmd + " ..."
    args = shlex.split(cmd)
    p = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = p.communicate()
    return StringIO(out)
```
