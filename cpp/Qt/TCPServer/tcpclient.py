# -*- coding: utf-8 -*-

# 2014-03-05T11:14+08:00

import logging
import random
import socket
import struct
import time

logging.basicConfig(
    format = '%(asctime)-15s %(levelname)s %(message)s ',
    filename = 'tcpclient.log', filemode = 'w')
logger = logging.getLogger('tcpclient_logger')
logger.setLevel(logging.DEBUG)

host, port = 'localhost', 7349

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

try:
    sock.connect((host, port))

    while True:
        time.sleep(2)
        
        filename = 'file{}.dat'.format(random.randint(0, 65536))
        filename = filename.encode('utf-8')
        totalsize = random.randint(0, 65536)
        fhead = struct.pack('qq%ds' % len(filename),
                            totalsize, len(filename), filename)
        logger.info(struct.unpack('qq%ds' % len(filename), fhead))
        sock.sendall(fhead)
finally:
    sock.close()


