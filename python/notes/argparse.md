1. An example of `fromfile_prefix_chars`

   > ```python
   > # https://github.com/AVGTechnologies/cppmangle/blob/master/cppmangle/__main__.py
   > from .mangle import mangle, demangle
   > from .cdecl import cdecl_sym
   > import argparse
   > 
   > def main():
   >     ap = argparse.ArgumentParser(fromfile_prefix_chars='@')
   >     ap.add_argument('name', nargs='+')
   >     args = ap.parse_args()
   > 
   >     for name in args.name:
   >         dem = demangle(name)
   >         print(cdecl_sym(dem))
   > ```

2. [argparse metavar for nargs='+' to get numbered arguments in help info?](https://stackoverflow.com/questions/48429221/argparse-metavar-for-nargs-to-get-numbered-arguments-in-help-info)

3. [Why is argparse not raising exceptions?](https://stackoverflow.com/questions/27458976/why-is-argparse-not-raising-exceptions)

4. https://github.com/kblin/ncbi-genome-download/blob/master/ncbi_genome_download/core.py

