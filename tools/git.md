
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

[Merge a special commit](https://stackoverflow.com/questions/881092/how-to-merge-a-specific-commit-in-git)

[Create a new repo from an existing repo's subdirectory](https://stackoverflow.com/questions/6680709/create-new-git-repo-from-already-existing-repos-subdirectory)

[Remove large .pack file created by git](https://stackoverflow.com/questions/11050265/remove-large-pack-file-created-by-git)

[Git: Clean up commits after moving subdirectory into a new repo](https://stackoverflow.com/questions/40716681/git-clean-up-commits-after-moving-subdirectory-into-a-new-repo)

[How to tear apart a repository: the Git way](https://www.atlassian.com/blog/git/tear-apart-repository-git-way)

[Detach (move) subdirectory into separate Git repository](https://stackoverflow.com/questions/359424/detach-move-subdirectory-into-separate-git-repository)

[git shortlog -sn](https://github.com/mixu/distsysbook)

[How to clone all remote branches in Git?](https://stackoverflow.com/questions/67699/how-to-clone-all-remote-branches-in-git)

[How do I list all remote refs?](https://stackoverflow.com/questions/42626068/how-do-i-list-all-remote-refs)

git diff <version1>..<version2> --stat

git whatchanged --since="three days ago" --oneline

git grep -i <...> # ignore case

git grep -l # list matched files

git grep -w # match whole word

git log --follow file

git log --follow --name-only file

[Is there a way to represent a directory tree in a Github README.md?](https://stackoverflow.com/questions/23989232/is-there-a-way-to-represent-a-directory-tree-in-a-github-readme-md)

[Squash all my commits into one for GitHub pull request](https://stackoverflow.com/questions/14534397/squash-all-my-commits-into-one-for-github-pull-request)

[Closing multiple issues in Github with a commit message](https://stackoverflow.com/questions/3547445/closing-multiple-issues-in-github-with-a-commit-message)

[How do you merge two Git repositories?](https://stackoverflow.com/questions/1425892/how-do-you-merge-two-git-repositories)

[Git removing commiter information](https://stackoverflow.com/questions/7013085/git-removing-commiter-information)

[git-blame -w](https://github.com/edenhill/librdkafka/issues/762)

[git grep](https://github.com/editorconfig/editorconfig-core-c/pull/57)

[How do I discard unstaged changes in Git?](https://stackoverflow.com/questions/52704/how-do-i-discard-unstaged-changes-in-git)

[git bisect tutorial](https://github.com/andschwa/git-bisect-tutorial)

[Difference between “git add -A” and “git add .”](https://stackoverflow.com/questions/572549/difference-between-git-add-a-and-git-add)

[how to apply multiple git patches in one shot](https://stackoverflow.com/questions/18494750/how-to-apply-multiple-git-patches-in-one-shot)

[git-gc-all](https://stackoverflow.com/questions/1904860/how-to-remove-unreferenced-blobs-from-my-git-repo)

[git bisect](http://www.ruanyifeng.com/blog/2018/12/git-bisect.html)

[git shallow submodule](https://github.com/denoland/deno/pull/2971/files)

[How to make shallow git submodules?](https://stackoverflow.com/questions/2144406/how-to-make-shallow-git-submodules)

[Is it possible to move/rename files in Git and maintain their history?](https://stackoverflow.com/questions/2314652/is-it-possible-to-move-rename-files-in-git-and-maintain-their-history)

https://github.com/microsoft/vcpkg/issues/8914

https://github.com/magicmonty/bash-git-prompt

[How to extract history of specific file[s] and write out to new empty branch?](https://stackoverflow.com/questions/44605145/githow-to-extract-history-of-specific-files-and-write-out-to-new-empty-branc/44606125?noredirect=1)

[git submodule update vs git submodule sync](https://stackoverflow.com/questions/45678862/git-submodule-update-vs-git-submodule-sync)

[Git Submodule update over https](https://stackoverflow.com/questions/11410017/git-submodule-update-over-https)

[GitHub: How to make a fork of public repository private?](https://stackoverflow.com/questions/10065526/github-how-to-make-a-fork-of-public-repository-private/30352360#30352360)

[How to properly mirror a git repository](http://blog.plataformatec.com.br/2013/05/how-to-properly-mirror-a-git-repository/)
```bash
$ git clone --mirror git@example.com/upstream-repository.git
$ cd upstream-repository.git
$ git push --mirror git@example.com/new-location.git
```

[How to grep (search) committed code in the Git history](https://stackoverflow.com/questions/2928584/how-to-grep-search-committed-code-in-the-git-history)

Client:

* [Git Clients](https://github.com/qianguyihao/Web/blob/master/00-%E5%89%8D%E7%AB%AF%E5%B7%A5%E5%85%B7/02-Git%E7%9A%84%E4%BD%BF%E7%94%A8.md)
* [Tower](https://www.git-tower.com/)
* [Fork](https://git-fork.com/)
* [GitUp](https://gitup.co/)
* [SmartGit](https://www.syntevo.com/smartgit/)

[Mirror a repo](http://blog.plataformatec.com.br/2013/05/how-to-properly-mirror-a-git-repository/)
> However, what we want with mirroring is to replicate the state of an origin repository (or upstream repository). By state, we mean all the branches (including master) and all the tags as well.

```bash
$ git clone --mirror git@example.com/upstream-repository.git
$ cd upstream-repository.git
$ git push --mirror git@example.com/new-location.git
```

[ORIG_HEAD, FETCH_HEAD, MERGE_HEAD etc](https://stackoverflow.com/questions/17595524/orig-head-fetch-head-merge-head-etc)

[git hook](https://githooks.com/)

[How can one change the timestamp of an old commit in Git?](https://stackoverflow.com/questions/454734/how-can-one-change-the-timestamp-of-an-old-commit-in-git)
```bash
git filter-branch --env-filter \
    'if [ $GIT_COMMIT = 119f9ecf58069b265ab22f1f97d2b648faf932e0 ]
     then
         export GIT_AUTHOR_DATE="Fri Jan 2 21:38:53 2009 -0800"
         export GIT_COMMITTER_DATE="Sat May 19 01:01:01 2007 -0700"
     fi'
```

[How can I get the Git commit hash in my PS script?](https://stackoverflow.com/questions/43962860/how-can-i-get-the-git-commit-hash-in-my-ps-script)

[Trying to find out if Git is installed via Powershell?](https://stackoverflow.com/questions/46743845/trying-to-find-out-if-git-is-installed-via-powershell)

[git diff ^M](https://help.github.com/en/github/using-git/configuring-git-to-handle-line-endings)
