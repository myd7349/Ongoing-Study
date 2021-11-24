* [pip is configured with locations that require TLS/SSL, however the ssl module in Python is not available](https://stackoverflow.com/questions/45954528/pip-is-configured-with-locations-that-require-tls-ssl-however-the-ssl-module-in)

* [How to get pip to work behind a proxy server](https://stackoverflow.com/questions/19080352/how-to-get-pip-to-work-behind-a-proxy-server)
  
  ```
  PS C:\Users\myd> $env:HTTP_PROXY='http://127.0.0.1:7079'
  PS C:\Users\myd> $env:HTTPS_PROXY='https://127.0.0.1:7079'
  PS C:\Users\myd> py -m pip install -U pywinauto
  ```
- [requirements.txt](https://pip.pypa.io/en/stable/user_guide/)

> ```
> python -m pip install -r requirements.txt
> ```

- [PyCon China 2021 演讲——Python 打包 101](https://frostming.com/2021/10-20/pycon-china-2021/)
- [Why you should use &#x60;python -m pip&#x60;](https://snarky.ca/why-you-should-use-python-m-pip/)
  - https://twitter.com/yihong0618/status/1483602607004618753
  
  - https://twitter.com/mariatta/status/1189243515739561985
    
    > 