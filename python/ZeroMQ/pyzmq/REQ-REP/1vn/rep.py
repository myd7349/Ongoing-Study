#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-12-24T14:34+08:00

# http://blog.ez2learn.com/2011/12/31/transport-lib-of-new-era-zeromq/

import os
import time
import zmq

def main():
    context = zmq.Context()

    socket = context.socket(zmq.REP)
    socket.connect('tcp://localhost:5556')

    print('Worker {} is running...'.format(os.getpid()))

    while True:
        # receive request
        a, b = socket.recv_multipart()
        #time.sleep(5)
        a = int(a.decode('utf-8'))
        b = int(b.decode('utf-8'))

        print('Compute {} + {} and send response'.format(a, b))
        socket.send_string(str(a + b))

if __name__ == '__main__':
    main()
