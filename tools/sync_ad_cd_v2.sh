#!/bin/bash
# A simple shell script to sync author date and committer date.

git rebase --committer-date-is-author-date

# References:
# [GIT: change commit date to author date](https://stackoverflow.com/questions/28536980/git-change-commit-date-to-author-date)
