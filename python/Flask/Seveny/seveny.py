#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-07-17T11:09+08:00

import sqlite3

import flask


# configuration
DATABASE = '/data/db/seveny.db'
DEBUG = True
SECRET_KEY = 'haha'
USERNAME = 'admin'
PASSWORD = 'default'


app = flask.Flask(__name__)
app.config.from_object(__name__)

