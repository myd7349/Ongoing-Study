[Import Readline](https://susam.net/blog/import-readline.html)

```python
import readline
import os

HISTORY_FILE = os.path.expanduser('~/.repl_history')
if os.path.exists(HISTORY_FILE):
    readline.read_history_file(HISTORY_FILE)

while True:
    try:
        line = input('> ')
        readline.write_history_file(HISTORY_FILE)
        print(sum([int(n) for n in line.split()]))
    except ValueError as e:
        print('error:', e)
    except (KeyboardInterrupt, EOFError):
        break
```

> At this point, it is worth mentioning that there are many interactive CLI tools that do not have line editing and history capabilities. They behave like our first toy REPL example in this post. Fortunately, there is the wonderful readline wrapper utility known as rlwrap that can be used to enable line editing and history in such tools. This utility can often be easily installed from package repositories of various operating systems.
