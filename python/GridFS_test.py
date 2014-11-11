#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-11-04T17:14+08:00

import hashlib
import os.path

########## 3rdparty ##########
import easygui
# http://api.mongodb.org/python/current/api/
# The PyMongo distribution contains three top-level packages for interacting
# with MongoDB: bson, gridfs and pymongo.
import gridfs
import pymongo
##############################

import utility

def get_file_md5(file_name, size = 1024 * 1024, upper = False):
    '''Calculate the MD5 digest of given file.

    file_name: Specify the target file whose MD5 you want to calculate
    size: Each time read size bytes from the file
    upper: Will the result upper-case or not
    '''
    md5_inst = hashlib.md5()
    with open(file_name, 'rb') as fp:
        # Read a binary file elegantly:
        # http://stackoverflow.com/questions/1035340/reading-binary-file-in-python
        # or you want to make a binary file object iterable?
        # http://stackoverflow.com/questions/4566498/python-file-iterator-over-a-binary-file-with-newer-idiom
        data = fp.read(size)
        while data:
            md5_inst.update(data)
            data = fp.read(size)
    return md5_inst.hexdigest().upper() if upper else \
           md5_inst.hexdigest()

@utility.benchmark(1)
def put_test(conn, db, collection_name, file_name):
    md5 = get_file_md5(file_name)
    
    with open(file_name, 'rb') as fp:
        fs = gridfs.GridFS(db, collection = collection_name)
        file_id = fs.put(fp, filename = os.path.basename(file_name))

        if fs.get(file_id).md5 == md5:
            return file_id, md5
        else:
            return None, None

@utility.benchmark(1)
def get_test(conn, db, collection_name, file_id, file_name):
    md5 = None
    with open(file_name, 'wb') as fp:
        fs = gridfs.GridFS(db, collection = collection_name)
        gridout = fs.get(file_id)
        md5 = gridout.md5
        chunk_size = gridout.chunkSize

        data = gridout.read(chunk_size)
        while data:
            fp.write(data)
            data = gridout.read(chunk_size)
    return get_file_md5(file_name) == md5
    
def main():
    db_name = 'pymongo_GridFS_test'
    collection_name = 'fs'

    client = pymongo.MongoClient(host = 'localhost', port = 27017)
    db = client[db_name]
    db.drop_collection(collection_name)

    # GridFS put test
    file_to_put = easygui.fileopenbox(
        msg = 'Select the file you want to put into GridFS:')
    if file_to_put:
        file_id, md5_digest = put_test(client, db, collection_name, file_to_put)
        if file_id:
            easygui.msgbox(
                msg = '"put" successfully!\nMD5: {}'.format(md5_digest),
                title = 'Congratulations!')
        else:
            easygui.msgbox(
                msg = 'Failed to "put"!', title = 'Error!')
            return

    # GridFS get test
    name, ext = os.path.splitext(os.path.basename(file_to_put))
    file_to_save = easygui.filesavebox(
        msg = 'Where do you want to save this file:',
        default = name + '_get_from_GridFS' + ext)
    if file_to_save:
        if get_test(client, db, collection_name, file_id, file_to_save):
            easygui.msgbox(
                msg = '"get" successfully!', title = 'Congratulations!')
        else:
            easygui.msgbox(msg = 'Failed to "get"!', title = 'Error!')

    client.drop_database(db_name)
    
if __name__ == '__main__':
    main()
