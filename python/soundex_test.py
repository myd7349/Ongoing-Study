#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2017-09-11T08:27+08:00

import contextlib
import sqlite3

import jellyfish  # pip install jellyfish


sql = '''
PRAGMA foreign_keys = off;
BEGIN TRANSACTION;

-- Table: users
CREATE TABLE users (
    id   INTEGER      NOT NULL
                       PRIMARY KEY AUTOINCREMENT,
    name VARCHAR (30) NOT NULL
);

INSERT INTO users (name) VALUES
    ('Dr. Zhang'),
    ('Michelle Green');

COMMIT TRANSACTION;
PRAGMA foreign_keys = on;
'''

with contextlib.closing(sqlite3.connect(':memory:')) as connection:
    connection.create_function('soundex', 1, jellyfish.soundex)
    
    with contextlib.closing(connection.executescript(sql)) as cursor:
        cursor.execute("SELECT id, name FROM users WHERE SOUNDEX(name) = SOUNDEX('Michael Green')")
        print(cursor.fetchall())


