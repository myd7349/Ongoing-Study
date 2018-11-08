
[Setting your Git username for every repository](https://help.github.com/articles/setting-your-username-in-git/)
```bash
$ git config --global user.name "Mona Lisa"
$ git config --global user.name
Mona Lisa
```

[Setting your Git username for a single repository](https://help.github.com/articles/setting-your-username-in-git/)
```bash
$ git config user.name "Mona Lisa"
$ git config user.name
Mona Lisa
```


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
git reset HEAD^ [--hard]
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


[Abort a merge](https://stackoverflow.com/questions/22565184/git-how-to-revert-after-a-merge-conflict-corruption)
```bash
git merge --abort
```


[Revert local changes](https://stackoverflow.com/questions/1146973/how-do-i-revert-all-local-changes-in-git-managed-project-to-previous-state)
```bash
git checkout .
```


[Delete a remote branch](https://makandracards.com/makandra/621-git-delete-a-branch-local-or-remote)
```bash
git push origin --delete <remote_branch_name>
```


[Specify author when committing](https://www.amazon.com/Version-Control-Git-collaborative-development/dp/1449316387)
```bash
git commit -m "Initial commit" --author="abc abc@def.com"
```


[Show difference between two commits](https://www.amazon.com/Version-Control-Git-collaborative-development/dp/1449316387)
```bash
git diff 34217e9 ec232cd
```

[Rename a file](https://www.amazon.com/Version-Control-Git-collaborative-development/dp/1449316387)

```bash
mv foo.html bar.html
git rm foo.html
git add bar.html
```

or

```bash
git mv foo.html bar.html
```


[Commit changes to a new branch](https://stackoverflow.com/questions/14655816/how-to-commit-changes-to-new-branch)
```bash
git checkout -b your-new-branch
git add <files>
git commit -m <message>
git push origin your-new-branch
```


[Pretty git branch graphs](https://stackoverflow.com/questions/1057564/pretty-git-branch-graphs)
```bash
git log --all --decorate --oneline --graph
```


https://stackoverflow.com/questions/2765421/how-do-i-push-a-new-local-branch-to-a-remote-git-repository-and-track-it-too

https://stackoverflow.com/questions/67699/how-to-clone-all-remote-branches-in-git

https://stackoverflow.com/questions/9537392/git-fetch-remote-branch

List all authors:

    - [git-authors](https://github.com/alessioalex/git-authors)
    - [List all developers on a project in Git](https://stackoverflow.com/questions/9597410/list-all-developers-on-a-project-in-git)
    - [List of authors in git since a given commit](https://stackoverflow.com/questions/6482436/list-of-authors-in-git-since-a-given-commit)
    - [List all authors of a particular git project](https://www.commandlinefu.com/commands/view/4519/list-all-authors-of-a-particular-git-project)


[How to delete a git remote tag?](https://stackoverflow.com/questions/5480258/how-to-delete-a-git-remote-tag)

```bash
git push origin :tagname
# Or
# git push --delete origin tagname
# If you want to delete a local tag:
# git tag --delete tagname
```
