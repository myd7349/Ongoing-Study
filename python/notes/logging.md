[How to encode log file?](https://stackoverflow.com/questions/21402530/how-to-encode-log-file)

[How to log to the same file in multiple modules](https://stackoverflow.com/questions/21721945/how-to-log-to-the-same-file-in-multiple-modules)

> ```pytho
> # If your program consists of multiple modules, here’s an example of how you 
> # could organize logging in it:
> 
> # myapp.py
> import logging
> import mylib
> 
> def main():
>     logging.basicConfig(filename='myapp.log', level=logging.INFO)
>     logging.info('Started')
>     mylib.do_something()
>     logging.info('Finished')
> 
> if __name__ == '__main__':
>     main()
> 
> # mylib.py
> import logging
> 
> def do_something():
>     logging.info('Doing something')
> ```

https://github.com/SergeyPirogov/webdriver_manager/blob/master/webdriver_manager/logger.py

[The Ins and Outs of Logging in Python, Part 1 | Monadical Consulting](https://monadical.com/posts/ins-and-outs-of-logging-in-python-part-one.html#)
