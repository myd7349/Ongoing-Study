* [pip is configured with locations that require TLS/SSL, however the ssl module in Python is not available](https://stackoverflow.com/questions/45954528/pip-is-configured-with-locations-that-require-tls-ssl-however-the-ssl-module-in)

* [How to get pip to work behind a proxy server](https://stackoverflow.com/questions/19080352/how-to-get-pip-to-work-behind-a-proxy-server)
```
PS C:\Users\myd> $env:HTTP_PROXY='http://127.0.0.1:7079'
PS C:\Users\myd> $env:HTTPS_PROXY='https://127.0.0.1:7079'
PS C:\Users\myd> py -m pip install -U pywinauto
```
