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

5. [argparse 的高级用法](https://frostming.com/2021/11-23/advanced-argparse/)

   - https://github.com/pdm-project/pdm/tree/main/pdm/cli/commands

6. [Python argparse: Is there a way to specify a range in nargs?](https://stackoverflow.com/questions/4194948/python-argparse-is-there-a-way-to-specify-a-range-in-nargs)

   ```python
   import argparse

   def required_length(nmin,nmax):
       class RequiredLength(argparse.Action):
           def __call__(self, parser, args, values, option_string=None):
               if not nmin<=len(values)<=nmax:
                   msg='argument "{f}" requires between {nmin} and {nmax} arguments'.format(
                       f=self.dest,nmin=nmin,nmax=nmax)
                   raise argparse.ArgumentTypeError(msg)
               setattr(args, self.dest, values)
       return RequiredLength

   parser=argparse.ArgumentParser(prog='PROG')
   parser.add_argument('-f', nargs='+', action=required_length(2,3))

   args=parser.parse_args('-f 1 2 3'.split())
   print(args.f)
   # ['1', '2', '3']

   try:
       args=parser.parse_args('-f 1 2 3 4'.split())
       print(args)
   except argparse.ArgumentTypeError as err:
       print(err)
   # argument "f" requires between 2 and 3 arguments
   ```

7. https://github.com/ewjoachim/pyler

8. https://github.com/meshpro/pygalmesh/blob/main/pygalmesh/_cli.py

9. https://github.com/lvgl/lv_binding_micropython/blob/master/gen/gen_mpy.py

10. https://github.com/WyattBlue/auto-editor/blob/master/auto_editor/__main__.py
