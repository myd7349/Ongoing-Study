2018-05-03T14:07+08:00

zipfile.py
```python
def main(args = None):
    import textwrap
    USAGE=textwrap.dedent("""\
        Usage:
            zipfile.py -l zipfile.zip        # Show listing of a zipfile
            zipfile.py -t zipfile.zip        # Test if a zipfile is valid
            zipfile.py -e zipfile.zip target # Extract zipfile into target dir
            zipfile.py -c zipfile.zip src ... # Create zipfile from sources
        """)
```

https://github.com/protocolbuffers/upb/blob/00e739648d816fae3972c9d51fef24940cf50539/tools/make_cmakelists.py#L197
