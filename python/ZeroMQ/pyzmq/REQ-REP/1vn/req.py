#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-12-24T14:27+08:00

# http://blog.ez2learn.com/2011/12/31/transport-lib-of-new-era-zeromq/

import random

import zmq

context = zmq.Context()

socket = context.socket(zmq.REQ)
socket.bind('tcp://*:5556')

# wait all workers connected
input('After all workers connecting to me, press "Enter" to continue:')

for i in range(9):
    a = random.randint(0, 100)
    b = random.randint(0, 100)
    print('Compute {} + {} ...'.format(a, b))

    # send request to peer

    # So, is there an interface named 'send_multipart_string(s)'?
    #socket.send_multipart([str(a), str(b)])
    socket.send_multipart([str(a).encode('utf-8'), str(b).encode('utf-8')])

    # receive response from peer
    rep = socket.recv_string()
    print(' =', rep)
