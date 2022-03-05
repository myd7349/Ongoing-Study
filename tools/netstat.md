[Get list of ports which are used](https://stackoverflow.com/questions/1438141/how-to-get-list-of-port-which-are-in-use-on-the-server)

[How to check opened/closed ports on my computer?](https://askubuntu.com/questions/538208/how-to-check-opened-closed-ports-on-my-computer)

> netstat -atn
> 
> netstat -ant | findstr "TIME_WAIT"

[netstat | Microsoft Docs](https://docs.microsoft.com/en-us/windows-server/administration/windows-commands/netstat)

[netstat does not show listening port of udp server?](https://stackoverflow.com/questions/41589797/netstat-does-not-show-listening-port-of-udp-server)

> ```
> netstat -n --udp --listen
> ```
