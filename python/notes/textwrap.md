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