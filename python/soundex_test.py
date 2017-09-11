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
    # It seems that Python3's builtin SQLite3 module doesn't support
    # the `SOUNDEX` function(May be the `SQLITE_SOUNDEX` option was
    # not enabled when the module was compiled).
    connection.create_function('soundex', 1, jellyfish.soundex)
    
    with contextlib.closing(connection.executescript(sql)) as cursor:
        cursor.execute("SELECT id, name FROM users WHERE SOUNDEX(name) = SOUNDEX('Michael Green')")
        print(cursor.fetchall())


# References:
# https://www.zhihu.com/question/65132459
# [Using Fuzzy Matching to Search by Sound with Python](https://doughellmann.com/blog/2012/03/03/using-fuzzy-matching-to-search-by-sound-with-python/)
# [How do I do a fuzzy match of company names in MYSQL with PHP for auto-complete?](https://stackoverflow.com/questions/369755/how-do-i-do-a-fuzzy-match-of-company-names-in-mysql-with-php-for-auto-complete)
