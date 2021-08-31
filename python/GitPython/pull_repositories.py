#! /usr/bin/env python3
# -*- coding: utf-8 -*-

from pathlib import Path
import sys

import git


def iter_repositories(search_path: Path):
    assert search_path.exists(), 'Path "{0}" doesn\'t exist.'.format(
        search_path)

    for entry in search_path.iterdir():
        if entry.is_dir():
            dot_git_folder = entry / '.git'
            if dot_git_folder.is_dir():
                yield entry


def pull_repository(repository_path: Path):
    assert repository_path.exists(), 'Repository "{0}" doesn\'t exist.'.format(
        repository_path)

    god = git.cmd.Git(repository_path)
    god.pull()


def main():
    search_path = Path(sys.argv[1]) if len(sys.argv) > 1 else Path.cwd()
    for repository_path in iter_repositories(search_path):
        print('Handling repository "{0}"...'.format(
            repository_path.relative_to(search_path)))
        pull_repository(repository_path)


if __name__ == '__main__':
    main()

# References:
# [How can I call 'git pull' from within Python?](https://stackoverflow.com/questions/15315573/how-can-i-call-git-pull-from-within-python)
# [What is the use of “assert” in Python?](https://stackoverflow.com/questions/5142418/what-is-the-use-of-assert-in-python)
# https://docs.python.org/3/library/pathlib.html
# https://github.com/orf/git-workspace
