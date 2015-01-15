#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-01-13T17:34+08:00

# "Hello World" example using ZeroMQ's DEALER-REP combination.
# A REQ-REP version can be find in "hwserver.py", "hwclient.py" under
# zguide/examples/Python.

# Hello World client.

def main():
    import os.path
    import sys
    import zmq

    if len(sys.argv) < 2:
        print('Usage:', os.path.split(__file__)[1], 'server ...')
        return

    request_cnt = 10
    
    context = zmq.Context()
    socket = context.socket(zmq.DEALER)

    # Establish connection with mutiple REP servers. The server addresses are
    # passed as a sequence of command line arguments. To make it simple, I omit
    # the code to validate a server address here.
    for server in set(sys.argv[1:]):
        socket.connect(server)

    # Using a DEALER client instead of a REQ gives us an asynchronous client
    # that can talk to multiple REP servers. And we'd be able to send off any
    # number of "Hello" requests without waiting for replies.
    for i in range(request_cnt):
        # Send an empty message part as the delimiter...
        socket.send(b'', flags = zmq.SNDMORE)
        # then followed by one or more body parts.
        socket.send_string('Hello #{}'.format(i))

    for i in range(request_cnt):
        message = socket.recv()
        if not message:
            message = socket.recv()
        print('Received message:', message.decode('utf-8'))

if __name__ == '__main__':    
    main()

# References:
# zmq_socket: http://api.zeromq.org/3-2:zmq-socket

