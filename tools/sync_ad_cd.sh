#!/bin/bash
# A simple shell script to sync author date and committer date.

LAST_COMMIT_HASH=$(git rev-parse HEAD)
LAST_COMMIT_AUTHOR_DATE=$(git log --pretty=format:"%ad" | head -n 1)
LAST_COMMIT_COMMITTER_DATE=$(git log --pretty=format:"%cd" | head -n 1)
echo "LAST_COMMIT_HASH          : ${LAST_COMMIT_HASH}"
echo "LAST_COMMIT_AUTHOR_DATE   : ${LAST_COMMIT_AUTHOR_DATE}"
echo "LAST_COMMIT_COMMITTER_DATE: ${LAST_COMMIT_COMMITTER_DATE}"
         
git filter-branch --env-filter \
    'if [ $GIT_COMMIT = ${LAST_COMMIT_HASH} ]
     then
         export GIT_AUTHOR_DATE="${LAST_COMMIT_AUTHOR_DATE}"
         export GIT_COMMITTER_DATE="${LAST_COMMIT_AUTHOR_DATE}"
     fi'

# References:
# [How do I set a variable to the output of a command in Bash?](https://stackoverflow.com/questions/4651437/how-do-i-set-a-variable-to-the-output-of-a-command-in-bash)
# [Difference between author and committer in Git?](https://stackoverflow.com/questions/18750808/difference-between-author-and-committer-in-git)
# [The shortest possible output from git log containing author and date](https://stackoverflow.com/questions/1441010/the-shortest-possible-output-from-git-log-containing-author-and-date)
# [GIT: change commit date to author date](https://stackoverflow.com/questions/28536980/git-change-commit-date-to-author-date)
