```
$ (base) C:\Users\myd7349>conda update anaconda
Collecting package metadata (current_repodata.json): failed

CondaHTTPError: HTTP 000 CONNECTION FAILED for url <https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/msys2/win-64/current_repodata.json>
Elapsed: -

An HTTP error occurred when trying to retrieve this URL.
HTTP errors are often intermittent, and a simple retry will get you on your way.
'https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/msys2/win-64'
```

[Using Anaconda behind a company proxy](https://docs.anaconda.com/anaconda/user-guide/tasks/proxy/)

> Update the .condarc file

My .condarc:

```
channels:
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/msys2/
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/cloud/conda-forge
  - https://mirrors.tuna.tsinghua.edu.cn/anaconda/pkgs/free/
  - defaults
proxy_servers:
  http: http://127.0.0.1:7078
  https: https://127.0.0.1:7078

```
