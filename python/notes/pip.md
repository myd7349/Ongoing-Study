* [pip is configured with locations that require TLS/SSL, however the ssl module in Python is not available](https://stackoverflow.com/questions/45954528/pip-is-configured-with-locations-that-require-tls-ssl-however-the-ssl-module-in)

* [How to get pip to work behind a proxy server](https://stackoverflow.com/questions/19080352/how-to-get-pip-to-work-behind-a-proxy-server)
  
  ```
  PS C:\Users\myd> $env:HTTP_PROXY='http://127.0.0.1:7079'
  PS C:\Users\myd> $env:HTTPS_PROXY='https://127.0.0.1:7079'
  PS C:\Users\myd> py -m pip install -U pywinauto
  pip 
  ```
- [requirements.txt](https://pip.pypa.io/en/stable/user_guide/)

> ```
> python -m pip install -r requirements.txt
> ```

- [PyCon China 2021 演讲——Python 打包 101](https://frostming.com/2021/10-20/pycon-china-2021/)

- [Why you should use &#x60;python -m pip&#x60;](https://snarky.ca/why-you-should-use-python-m-pip/)
  
  - https://twitter.com/yihong0618/status/1483602607004618753
  
  - https://twitter.com/mariatta/status/1189243515739561985

- [pip install using proxy in a virtual environment](https://stackoverflow.com/questions/37877871/pip-install-using-proxy-in-a-virtual-environment)

- [How to get pip to work behind a proxy server [duplicate]](https://stackoverflow.com/questions/19080352/how-to-get-pip-to-work-behind-a-proxy-server)

- [How can i create a new virtualenv using proxy? · Issue #1156 · pypa/virtualenv · GitHub](https://github.com/pypa/virtualenv/issues/1156)
  
  > ```
  > mkdir -p /opt/pypi/downloads
  > pushd /opt/pypi/downloads
  > pip download --no-cache --proxy http://proxy:3128 setuptools wheel pip
  > popd
  > virtualenv --no-download --extra-search-dir /opt/pypi/downloads virtualenv
  > ```

- [Wheel file installation](https://stackoverflow.com/questions/28002897/wheel-file-installation)
  
  ```
  pip install wheel
  ```

- [pip issue installing almost any library](https://stackoverflow.com/questions/16370583/pip-issue-installing-almost-any-library)

- [Installation - pip documentation v22.0.4](https://pip.pypa.io/en/stable/installation/)
  
  >  py -m ensurepip --upgrade
  
  or:
  
  > Download the script, from https://bootstrap.pypa.io/get-pip.py.
  > 
  > >  py get-pip.py

- [pip with embedded python - Stack Overflow](https://stackoverflow.com/questions/42666121/pip-with-embedded-python)

- [最推荐使用pip的方式](https://www.dongwm.com/post/you-should-use-python-m-pip/)

- [Installing specific package version with pip](https://stackoverflow.com/questions/5226311/installing-specific-package-version-with-pip)
