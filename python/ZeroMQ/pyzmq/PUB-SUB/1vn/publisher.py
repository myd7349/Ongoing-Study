#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-12-25T16:55+08:00

# http://blogs.ejb.cc/archives/5556/zeromq-via-c-sharp-a-communication-pattern

import zmq

context = zmq.Context()
socket = context.socket(zmq.PUB)
socket.bind('tcp://*:5556')

i = 0
while True:
    if i % 5 == 0:
        msg = 'Kiwi   {}'.format(i)
    elif i % 2 == 0:
        msg = 'Apple  {}'.format(i)
    else:
        msg = 'Orange {}'.format(i)
    print(msg)
    socket.send_string(msg)
    i += 1
