#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-11-22T17:02+08:00

# A Python version of `type-o-server` described in `HTTP: The Definitive Guide`.

import io
import socket
import sys


def line_buffering(sock, buffersize=4096):
    buffer = sock.recv(buffersize)
    buffering = True
    while buffering:
        if b'\n' in buffer:
            line, buffer = buffer.split(b'\n', 1)
            yield line + b'\n'
        else:
            more = sock.recv(buffersize)
            if not more:
                buffering = False
            else:
                buffer += more
                
    if buffer:
        yield buffer


def main():
    # (1) Use port 8080 by default, unless overridden on command line
    port = int(sys.argv[1], 0) if len(sys.argv) > 1 else 8080

    # (2) Create local TCP socket and set it to listen for connections
    with socket.socket(proto=socket.getprotobyname('TCP')) as sock:
        sock.bind(('', port))
        sock.listen()

        # (3) Print a startup message
        print('    <<<Type-o-Server Accepting on Port {0}>>>\n\n'.format(port))

        while True:
            # (4) Wait for a connection
            conn, address = sock.accept()

            # (5) Print who the connection is from
            hostname, aliaslist, ipaddrlist = socket.gethostbyaddr(address[0])
            print("    <<<Request From '{0}'>>>\n".format(hostname))

            # (6) Read request msg until blank line, and print on screen
            line = next(line_buffering(conn))
            print(line)

            # (7) Prompt for response message, and input response lines,
            #     sending response lines to client, until solitary "."
            print("    <<<Type Response Followed by '.'>>>\n")
            line = input().strip()
            while line:
                conn.send(line.encode('utf-8'))
                if line.endswith('.'):
                    break
                line = input().strip()

        sock.close()


if __name__ == '__main__':
    main()
