##### os.devnull

2016-11-28T15:00+08:00

[Google/benchmark](https://github.com/google/benchmark)/mingw.py:

```python
def unpack(archive, location, log = EmptyLogger()):
    '''
    Unpacks a mingw-builds archive
    '''
    sevenzip = find_7zip(log)
    log.info('unpacking %s', os.path.basename(archive))
    cmd = [sevenzip, 'x', archive, '-o' + location, '-y']
    log.debug(' - %r', cmd)
    with open(os.devnull, 'w') as devnull:
        subprocess.check_call(cmd, stdout = devnull)
```

This code snippet shows when to use `os.devnull`.

[Redirecting stdout to "nothing" in python](https://stackoverflow.com/questions/6735917/redirecting-stdout-to-nothing-in-python)

[Redirect stdout to a file in Python?](https://stackoverflow.com/questions/4675728/redirect-stdout-to-a-file-in-python)

##### os.replace

https://github.com/psf/requests/blob/main/requests/utils.py

```python
@contextlib.contextmanager
def atomic_open(filename):
    """Write a file to the disk in an atomic fashion"""
    replacer = os.rename if sys.version_info[0] == 2 else os.replace
    tmp_descriptor, tmp_name = tempfile.mkstemp(dir=os.path.dirname(filename))
    try:
        with os.fdopen(tmp_descriptor, 'wb') as tmp_handler:
            yield tmp_handler
        replacer(tmp_name, filename)
    except BaseException:
        os.remove(tmp_name)
        raise
```

https://docs.python.org/3/library/os.html

> If you want cross-platform overwriting of the destination, use [`replace()`](https://docs.python.org/3/library/os.html#os.replace).

##### Number of CPUs

https://github.com/wxWidgets/Phoenix/blob/master/buildtools/build_wxwidgets.py

```python
def numCPUs():
    """
    Detects the number of CPUs on a system.
    This approach is from detectCPUs here: http://www.artima.com/weblogs/viewpost.jsp?thread=230001
    """
    # Linux, Unix and MacOS:
    if hasattr(os, "sysconf"):
        if "SC_NPROCESSORS_ONLN" in os.sysconf_names:
            # Linux & Unix:
            ncpus = os.sysconf("SC_NPROCESSORS_ONLN")
            if isinstance(ncpus, int) and ncpus > 0:
                return ncpus
        else: # OSX:
            p = subprocess.Popen("sysctl -n hw.ncpu", shell=True, stdout=subprocess.PIPE)
            return p.stdout.read()

    # Windows:
    if "NUMBER_OF_PROCESSORS" in os.environ:
            ncpus = int(os.environ["NUMBER_OF_PROCESSORS"]);
            if ncpus > 0:
                return ncpus
    return 1 # Default
```

##### Set Environment Variable

[How to set environment variables in Python?](https://stackoverflow.com/questions/5971312/how-to-set-environment-variables-in-python)

> ```python
> os.environ["DEBUSSY"] = "1"
> ```

##### os.urandom

https://github.com/p-ranav/lc/blob/master/utils/make_large_file.py

```python
import argparse
import os


def get_file_size(size_in_units, unit):
    if unit == 'MB':
        file_size_in_bytes = size_in_units * 1024 * 1024
    elif unit == 'GB':
        file_size_in_bytes = size_in_units * 1024 * 1024 * 1024

    return file_size_in_bytes


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Make large files of arbitrary size to test lc')
    parser.add_argument('-s', '--size', help='size of file in Gigabytes', type=int, default=1)
    parser.add_argument('-m', '--megabytes', help='specify the size in Megabytes', action='store_true')
    args = parser.parse_args()

    if args.megabytes:
        unit = 'MB'
    else:
        unit = 'GB'

    size = get_file_size(args.size, unit)
    file_name = f'large_file_{args.size}{unit}'

    with open(file_name, 'wb') as fout:
        fout.write(os.urandom(size))
```
