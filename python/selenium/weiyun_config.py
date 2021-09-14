#!/usr/bin/env python3
# coding: utf-8

import json
import os.path
import sys
import types

APP_ROOT_DIR = os.path.dirname(sys.argv[0])

CONFIG_FILE_NAME = 'weiyun_helper.json'
CONFIG_FILE_PATH = os.path.join(APP_ROOT_DIR, CONFIG_FILE_NAME)

WEIYUN_HOMEPAGE = 'https://www.weiyun.com/'
WEIYUN_SHARE_URL_RE_B = br'https://share\.weiyun\.com/[A-Za-z0-9]{8}'
WEIYUN_SHARE_URL_RE = WEIYUN_SHARE_URL_RE_B.decode('latin')

WEIYUN_UPLOAD_BUTTON_XPATH = '/html/body/div[1]/div/div[1]/div/div[2]/div[1]/div/div/div[1]'
WEIYUN_SAVE_BUTTON_XPATH = '/html/body/div/div/div[2]/div/div/div[1]/div[1]/div/div/div[1]/div[1]/div/div'
WEIYUN_SAVE_OK_BUTTON_XPATH = '/html/body/div[2]/div/div[3]/button[2]'

KNOWN_BROWSERS = frozenset(('Chrome', 'Edge', 'Firefox', 'Safari'))

COOKIES_FILE_NAME_DICT = {
    'Chrome': 'cookies.chrome.json',
    'Edge': 'cookies.edge.json',
    'Firefox': 'cookies.firefox.json',
    'Safari': 'cookies.safari.json',
}

DEFAULT_CONFIG = {
    'browser': 'Firefox',
    'browser_driver_path': '',
    'login_timeout_in_seconds': 300,
}


class InvalidConfigException(Exception):
    pass


def get_cookies_file_path(config):
    return os.path.join(APP_ROOT_DIR, COOKIES_FILE_NAME_DICT[config.browser])


def default_config():
    return types.SimpleNamespace(**DEFAULT_CONFIG)


def load(config_file):
    if os.path.exists(config_file):
        with open(config_file, 'r', encoding='utf-8') as fp:
            config = json.load(fp)

            if 'browser' not in config or not isinstance(
                    config['browser'], str):
                config['browser'] = DEFAULT_CONFIG['browser']
            elif config['browser'] not in KNOWN_BROWSERS:
                raise InvalidConfigException(
                    'Unknown browser: {0}. Known browsers: {1}'.format(
                        config['browser'], KNOWN_BROWSERS))

            if 'browser_driver_path' not in config or not isinstance(
                    config['browser_driver_path'],
                    str) or not config['browser_driver_path']:
                config['browser_driver_path'] = DEFAULT_CONFIG[
                    'browser_driver_path']
            elif not os.path.isfile(
                    config['browser_driver_path']) and not os.path.isdir(
                        config['browser_driver_path']):
                raise InvalidConfigException(
                    'Browser driver path \'{0}\' is neither an existing file or directory.'
                    .format(config['browser_driver_path']))

            return types.SimpleNamespace(**config)
    else:
        return default_config()


def store(config, config_file):
    with open(config_file, 'w', encoding='utf-8') as fp:
        json.dump(config.__dict__, fp, indent=4, sort_keys=True)


# References:
# [What's the best practice using a settings file in Python?](https://stackoverflow.com/questions/5055042/whats-the-best-practice-using-a-settings-file-in-python)
# [C-like structures in Python](https://stackoverflow.com/questions/35988/c-like-structures-in-python)
# [How to convert JSON data into a Python object](https://stackoverflow.com/questions/6578986/how-to-convert-json-data-into-a-python-object)
# [How to initialize a dict from a SimpleNamespace?](https://stackoverflow.com/questions/52783883/how-to-initialize-a-dict-from-a-simplenamespace)
# [Python update a key in dict if it doesn't exist](https://stackoverflow.com/questions/42315072/python-update-a-key-in-dict-if-it-doesnt-exist/42315120)
# [Proper way to declare custom exceptions in modern Python?](https://stackoverflow.com/questions/1319615/proper-way-to-declare-custom-exceptions-in-modern-python)
