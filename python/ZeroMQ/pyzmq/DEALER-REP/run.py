#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-01-14T17:11+08:00

from multiprocessing import Process
import os

if os.name == 'posix':
    py = 'python3'
elif os.name == 'nt':
    py = 'py -3'
else:
    raise SystemExit('Unsupported platform')

def run(args):
    Process(target = os.system, args = ('{} {}'.format(py, args), )).start()
    
if __name__ == '__main__':
    servers = 'tcp://*:5555', 'tcp://*:5556'
    
    # Firstly, start several REP servers.
    for server_id, server_addr in zip(range(len(servers)), servers):
        run('hwserver.py {} {}'.format(server_id, server_addr))
        
    # Secondly, start the DEALER client.
    run('hwclient.py {} && pause'.format(' '.join(serv.replace('*', 'localhost') for serv in servers)))
