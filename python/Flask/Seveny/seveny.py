#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-07-17T11:09+08:00

import os
import sqlite3

from flask import Flask, abort, flash, g, redirect, \
     render_template, request, session, url_for

import fileutil


module_path = os.path.dirname(__file__)
path_of = lambda resource: os.path.join(module_path, resource)

# configuration
DATABASE = path_of('data/db/seveny.db')
DEBUG = True
SECRET_KEY = 'haha'

config_envvar = 'FLASK_SETTINGS'
if config_envvar not in os.environ:
    os.environ[config_envvar] = fileutil.replace_ext(__file__, '.cfg')

app = Flask(__name__)
#app.config.from_envvar(config_envvar, slient=True)
app.config.from_object(__name__)


def init_db():
    import contextlib

    with contextlib.closing(connect_db()) as db:
        with app.open_resource(path_of('schema.sql'), mode='r') as fp:
            db.cursor().executescript(fp.read())
        db.commit()


def connect_db():
    return sqlite3.connect(app.config['DATABASE'])


@app.before_request
def before_request():
    g.db = connect_db()


@app.teardown_request
def teardown_request(exception):
    db = getattr(g, 'db', None)
    if db:
        db.close()


@app.route('/')
def index():
    if not session.get('logged_in'):
        return redirect(url_for('login'))
    else:
        return redirect(url_for('employee', name=g.user))


@app.route('/login', methods=['GET', 'POST'])
def login():
    if session.get('logged_in'):
        return redirect(url_for('employee', name=g.user))

    cursor = g.db.execute('select count(*) from employees')
    if not cursor.fetchone()[0]:
        # Create an administrator account
        g.db.execute('insert into employees values (?, ?, ?, ?, ?)',
                     ['admin', 'admin', '', '<Unknown>', 0])
        g.db.commit()

    error = None
    if request.method == 'POST':
        user = request.form['username']
        pwd = request.form['password']

        if not user or not pwd:
            error = '用户名和密码都不能为空！'
        else:
            record = g.db.execute('select user, pwd from employees where user = \'{}\''.format(user)).fetchone()
            if not record:
                error = '用户“{}”不存在。'.format(user)
            elif pwd != record[1]:
                error = '密码不正确。'
            else:
                session['logged_in'] = True
                setattr(g, 'user', user)
                flash('Welcome {}!'.format(user))
                return 'haha'
    return render_template('login.html', error=error)


@app.route('/logout')
def logout():
    session.pop('logged_in', None)
    g.user = None
    flash('您已退出登录。')
    return redirect(url_for('login'))


@app.route('/employee/<name>')
def employee(name):
    if session.get('logged_in'):
        return '欢迎您！' + name
    else:
        abort(404)


@app.route('/administrator/<name>')
def administrator(name):
    if session.get('logged_in'):
        return '欢迎您！管理员：' + name
    else:
        abort(404)


if __name__ == '__main__':
    if not os.path.exists(app.config['DATABASE']):
        dirname = os.path.dirname(app.config['DATABASE'])
        if not os.path.exists(dirname):
            from distutils.dir_util import mkpath
            mkpath(dirname)
        init_db()

    app.debug = True
    app.run(host='0.0.0.0')

