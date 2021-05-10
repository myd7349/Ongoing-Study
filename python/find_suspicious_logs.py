# -*- coding: utf-8 -*-

import pathlib
import sys


def main():
    log_dirs = []

    if len(sys.argv) == 1:
        log_dirs.append(pathlib.Path.cwd())
    else:
        log_dirs += [pathlib.Path(path) for path in sys.argv[1:]]

    for path in log_dirs:
        if not path.exists():
            print('"{0}" doesn\'t exist.'.format(path))
            continue

        log_files = []
        if path.is_file():
            if path.match('*.log'):
                log_files.append(path)
            else:
                print('"{0}" is not a log file.'.format(path))
                continue
        elif path.is_dir():
            log_files += path.rglob('*.log')
        else:
            print('"{0}" is neither a file nor a directory.'.format(path))
            continue

        for log_file_path in log_files:
            startup_count = 0
            shutdown_count = 0

            with log_file_path.open('rb') as fp:
                for line in fp:
                    if b'Startup' in line:
                        startup_count += 1
                    elif b'Shutdown' in line:
                        shutdown_count += 1

            if startup_count != shutdown_count:
                print(log_file_path, 'Startup:', startup_count, 'Shutdown: ',
                      shutdown_count)


if __name__ == '__main__':
    main()

# References:
# [python路径操作新标准：pathlib 模块](https://zhuanlan.zhihu.com/p/139783331)
# [为什么你应该开始习惯使用 pathlib？](https://www.jianshu.com/p/ae194371cf7c)
