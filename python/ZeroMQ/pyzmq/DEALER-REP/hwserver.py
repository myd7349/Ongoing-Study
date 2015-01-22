#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-01-13T16:45+08:00

# "Hello World" example using ZeroMQ's DEALER-REP combination.
# A REQ-REP version can be find in "hwserver.py", "hwclient.py" under
# zguide/examples/Python.

# Hello World server.

def main():
    import os.path
    import sys
    import time
    import zmq # pyzmq is needed

    if len(sys.argv) != 3:
        print('Usage: id', os.path.split(__file__)[1], 'address')
        return
    
    context = zmq.Context()
    socket = context.socket(zmq.REP)
    socket.bind(sys.argv[2])

    while True:
        # Wait for next request from client
        message = socket.recv_string()
        print('Received request:', message)

        # Do some "work"
        time.sleep(1)
        
        # Send reply back to client
        socket.send_string('World from REP server #{}'.format(sys.argv[1]))
    
if __name__ == '__main__':
    main()

# References:
# ZeroMQ - The Guide: http://zguide.zeromq.org/page:all
# zguide: https://github.com/imatix/zguide
# zguide-cn: https://github.com/anjuke/zguide-cn
# zmq_socket: http://api.zeromq.org/3-2:zmq-socket
