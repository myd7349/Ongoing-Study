1. [Generate SSH keypair](https://docs.gitlab.com/ce/ssh/README.html):

```bash
ssh-keygen -t ed25519 -C "myd7349 freedesktop.gitlab"
type id_ed25519.pub | clip
```

2. [Access GitLab via HTTPS](https://stackoverflow.com/questions/60272933/smartgit-unable-to-push-remote-http-basic-access-denied):
> git config credential.helper
>
>If it returns "manager", open your Windows Credentials Manager and check if credentials are already stored for gitlab.com.
>If so, delete it, then push again: Git should ask for your credentials. Do enter your PAT (Personal Access Token) as password.

https://stackoverflow.com/questions/41263662/how-to-solve-access-denied-in-gitlab

3. [Show your public key](https://stackoverflow.com/questions/41148750/generating-a-gitlab-ssh-key-from-windows)
> ON windows if you have git for windows installed, run git-gui. Then click Help then click Show Ssh Key, then click Generate Key.
