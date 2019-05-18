# -*- coding: utf-8 -*-

import socket

import netifaces  # pip3 install netifaces


hostname = socket.gethostname()
host = socket.gethostbyname(hostname)
    
print(f'Host name: {hostname}')
print(f'Host: {host}')
    
for interface in netifaces.interfaces():
    print(f'Interface: {interface}')
        
    addr = netifaces.ifaddresses(interface)
    print(f'Address: {addr}')


# References:
# https://stackoverflow.com/questions/24196932/how-can-i-get-the-ip-address-of-eth0-in-python
