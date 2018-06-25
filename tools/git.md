How to ignore files from commit?
- [Untrack files from git temporarily](https://stackoverflow.com/questions/6964297/untrack-files-from-git-temporarily/6964322)
- [Can I 'git commit' a file and ignore its content changes?](https://stackoverflow.com/questions/3319479/can-i-git-commit-a-file-and-ignore-its-content-changes)
- [GIT — Exclude / Ignore Files from commit](https://stackoverflow.com/questions/7070659/git-exclude-ignore-files-from-commit)


clone from SVN repo:
```bash
git svn clone --stdlayout <SVN repo link>
```


[Revert the most recent commit:](https://stackoverflow.com/questions/927358/how-to-undo-the-most-recent-commits-in-git)
```
git reset HEAD~
```


[Change the author and committer name and e-mail of multiple commits in Git](https://stackoverflow.com/questions/750172/change-the-author-and-committer-name-and-e-mail-of-multiple-commits-in-git)


[Undo the most recent push:](http://christoph.ruegg.name/blog/git-howto-revert-a-commit-already-pushed-to-a-remote-reposit.html)
```
git reset HEAD^ --hard
git push -f
```


[Remove a submodule](https://stackoverflow.com/questions/1260748/how-do-i-remove-a-submodule)
```bash
mv <submodule_path> <submodule_path>_tmp  # Rename the submodule path
git submodule deinit -f -- <submodule_path>
rm -rf .git/modules/<submodule_path>
git rm -f <submodule_path>
rm -rf <submodule_path>_tmp
```


[Check out a specific commit of a submodule](https://stackoverflow.com/questions/10914022/how-to-check-out-specific-version-of-a-submodule-using-git-submodule)
```bash
git submodule add git://some_repository.git <some_repository_local_name>
cd <some_repository_local_name>
git checkout <some_commit>
```

[Undo checkout](https://stackoverflow.com/questions/3601911/how-do-i-undo-a-checkout-in-git)
```bash
git checkout master
```


[Update submodule]
```bash
git submodule update --remote
```
