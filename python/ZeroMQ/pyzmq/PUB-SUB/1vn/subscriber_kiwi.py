#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-12-25T17:02+08:00

# http://blogs.ejb.cc/archives/5556/zeromq-via-c-sharp-a-communication-pattern

import zmq

context = zmq.Context()
socket = context.socket(zmq.SUB)
socket.connect('tcp://localhost:5556')

socket.setsockopt_string(zmq.SUBSCRIBE, 'Kiwi')

while True:
    print(socket.recv_string())
