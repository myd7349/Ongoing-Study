Servers:

- [Bonobo](https://github.com/jakubgarfield/Bonobo-Git-Server)

- [git](https://github.com/msysgit/msysgit/wiki/Setting-up-a-Git-server-on-Windows-using-Git-for-Windows-and-CopSSH)

- gogs

Clients:

- [Fork](https://git-fork.com/)
- [GitTouch](https://github.com/git-touch)
- [SmartGit](https://www.syntevo.com/smartgit/)
- Source Tree
- TortoiseGit
- [Tower](https://www.git-tower.com/)

CI/CD:

- [Bamboo](https://confluence.atlassian.com/bamboo)

Tools:

- [git-big-picture](https://github.com/git-big-picture/git-big-picture)
- [git-crypt](https://github.com/AGWA/git-crypt)

Software

- [SparkleShare](https://github.com/hbons/SparkleShare)

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

[Git 在不同的项目使用不同的author](https://www.kawabangga.com/posts/2889)

[Is it possible to have different Git configuration for different projects?](https://stackoverflow.com/questions/8801729/is-it-possible-to-have-different-git-configuration-for-different-projects)

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

[GIT: change commit date to author date](https://stackoverflow.com/questions/28536980/git-change-commit-date-to-author-date)

> git rebase --committer-date-is-author-date

[How can I get the Git commit hash in my PS script?](https://stackoverflow.com/questions/43962860/how-can-i-get-the-git-commit-hash-in-my-ps-script)

[Trying to find out if Git is installed via Powershell?](https://stackoverflow.com/questions/46743845/trying-to-find-out-if-git-is-installed-via-powershell)

[git diff ^M](https://help.github.com/en/github/using-git/configuring-git-to-handle-line-endings)

[Configure Git to use a proxy](https://gist.github.com/evantoli/f8c23a37eb3558ab8765)

[Git apply error : unrecognized input](https://stackoverflow.com/questions/51542622/git-apply-error-unrecognized-input)

> git diff --no-color

What does `feat` mean in git commit message? For example, [feat: :sparkles: lambda closure](https://github.com/Danielmelody/Ruschm/pull/29). By searching `git feat` in popular search engines, I found these articles:

- [Semantic Commit Messages](https://gist.github.com/joshbuchea/6f47e86d2510bce28f8e7f42ae84c716)
- [Commit message 和 Change log 编写指南](https://www.ruanyifeng.com/blog/2016/01/commit_message_change_log.html)
- [AngularJS Git Commit Message Conventions](https://github.com/angular/angular/blob/master/CONTRIBUTING.md#commit)
- [Git 提交信息样式指南](https://github.com/udacity/frontend-nanodegree-styleguide-zh/blob/master/%E5%89%8D%E7%AB%AF%E5%B7%A5%E7%A8%8B%E5%B8%88%E7%BA%B3%E7%B1%B3%E5%AD%A6%E4%BD%8D%E6%A0%B7%E5%BC%8F%E6%8C%87%E5%8D%97%20-%20Git.md)
- [git commit 提交规范 & 规范校验](https://blog.csdn.net/y491887095/article/details/80594043)

In the last article listed above, it mentioned `commitlint` and `husky`, which can both be installed via `npm`.

> git config --global http.proxy http://127.0.0.1:7079

[Reset git proxy to default configuration](https://stackoverflow.com/questions/11265463/reset-git-proxy-to-default-configuration)

> git config --global --unset core.gitproxy
> git config --global --unset https.proxy

[git-sizer](https://github.com/github/git-sizer)

git-lfs:

https://github.com/SixLabors/ImageSharp/blob/master/tests/Images/Input/Bmp/Car.bmp

https://docs.github.com/en/github/managing-large-files/installing-git-large-file-storage

https://github.com/gongminmin/Coilgun

> NOTE: Please turn on git LFS when cloning this project.

git ls-tree:

> ```
> # https://github.com/microsoft/vcpkg/pull/17597
> git ls-tree -d HEAD -- ports/
> ```

git grep option -- CMakeLists.txt

git grep option -- *.txt *.cmake

[git rev-list --count HEAD](https://github.com/ArthurSonzogni/FTXUI/blob/2406e20f3640c6bf8fac56860105744b6bafd2f9/CMakeLists.txt#L7)

https://github.com/arxanas/git-branchless

https://github.com/conventional-changelog/commitlint

https://github.com/pre-commit/pre-commit

- https://github.com/ManimCommunity/manim/blob/main/.pre-commit-config.yaml

[Is it possible to cherry-pick a commit from another git repository?](https://stackoverflow.com/questions/5120038/is-it-possible-to-cherry-pick-a-commit-from-another-git-repository)

```
# https://github.com/SixLabors/ImageSharp
git config --system core.longpaths true
```

[New in Git: switch and restore](https://www.banterly.net/2021/07/31/new-in-git-switch-and-restore/)

[```master``` and ```development```  branch](https://github.com/CppMicroServices/CppMicroServices)

> The Git repository contains two eternal branches, [master](https://github.com/CppMicroServices/CppMicroServices/tree/master/) and [development](https://github.com/CppMicroServices/CppMicroServices/tree/development/). The master branch contains production quality code and its HEAD points to the latest released version. The development branch is the default branch and contains the current state of development. Pull requests by default target the development branch. See the [:ref:`CONTRIBUTING `](https://github.com/CppMicroServices/CppMicroServices#id5) file for details about the contribution process.

[Git pulling a branch from another repository?](https://stackoverflow.com/questions/14383212/git-pulling-a-branch-from-another-repository)

> ```
> git remote add fork <url of fork>
> git fetch fork
> git checkout -b fork_branch fork/<branch>
> ```

[gitfs](https://github.com/presslabs/gitfs)

https://github.com/klaussilveira/gitlist

https://github.com/chriswalz/bit

In PowerShell, `git push origin -d v1.2.3(2021.08.30)` will try to delete tag `v1.2.3` instead of `v1.2.3(2021.08.30)`.

https://github.com/flameshot-org/flameshot/blob/ce336a6a70725ba47db54092026caab8c1f84c52/src/CMakeLists.txt#L221

> ```cmake
> execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD OUTPUT_VARIABLE FLAMESHOT_GIT_HASH)
> ```
> 
> ```cpp
> // https://github.com/flameshot-org/flameshot/blob/ce336a6a70725ba47db54092026caab8c1f84c52/src/utils/globalvalues.cpp#L15
> QString GlobalValues::versionInfo()
> {
>     return QStringLiteral("Flameshot " APP_VERSION " (" FLAMESHOT_GIT_HASH ")"
>         "\nCompiled with Qt " QT_VERSION_STR);
> }
> ```

https://github.com/jesseduffield/lazygit

[别想偷我源码：通用的针对源码泄露利用程序的反制（常见工具集体沦陷）](https://drivertom.blogspot.com/2021/08/git.html)

> index文件中包含了这个项目中的各个文件的信息，包括文件路径和Git对象的对应的40位哈希值。在这里我们不需要对Git对象理解的很深入，只需要知道里面包含了文件内容，是让攻击者垂涎欲滴的东西就可以了。
> 
> 想要拿到Git对象，就需要转去objects目录。objects目录存放了所有的git对象，对于一个git对象，40位哈希的前两位会作为目录名，而后面的38位会作为文件名，存在objects下面。举个例子，一个Git对象那个的hash是cb75d8439f004f41d5f85ffa5f8d017df395651a，那么它就会被存在cb/75d8439f004f41d5f85ffa5f8d017df395651a。
> 
> 知道了这些信息之后，就可以知道Git泄露攻击是如何进行的了，首先攻击者访问index文件，解析后得到文件名和对象哈希。接着按着对象哈希一个一个去objects目录获取到Git对象，解析后得到文件。

[Git - index-format Documentation](https://git-scm.com/docs/index-format)

[gum](https://github.com/gauseen/gum)

https://twitter.com/yihong0618/status/1475472422836924417

[lazygit](https://github.com/jesseduffield/lazygit)
