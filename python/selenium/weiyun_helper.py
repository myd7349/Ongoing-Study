#!/usr/bin/env python3
# coding: utf-8

import json
import os.path
import random
import re
import sys
import time

from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as Expect
from selenium.webdriver.common.by import By
from selenium.common.exceptions import TimeoutException

APP_ROOT_DIR = os.path.dirname(sys.argv[0])
COOKIES_FILE_NAME = 'cookies.json'
COOKIES_FILE_PATH = os.path.join(APP_ROOT_DIR, COOKIES_FILE_NAME)

WEIYUN_HOMEPAGE = 'https://www.weiyun.com/'
WEIYUN_SHARE_URL_RE_B = br'https://share\.weiyun\.com/[A-Za-z0-9]{8}'
WEIYUN_SHARE_URL_RE = WEIYUN_SHARE_URL_RE_B.decode('latin')

WEIYUN_UPLOAD_BUTTON_XPATH = '/html/body/div[1]/div/div[1]/div/div[2]/div[1]/div/div/div[1]'
WEIYUN_SAVE_BUTTON_XPATH = '/html/body/div/div/div[2]/div/div/div[1]/div[1]/div/div/div[1]/div[1]/div/div'
WEIYUN_SAVE_OK_BUTTON_XPATH = '/html/body/div[2]/div/div[3]/button[2]'


class WeiYunHelper:
    def __init__(self):
        self._browser = webdriver.Firefox()

    def login(self, timeout_in_seconds=300):
        if os.path.exists(COOKIES_FILE_PATH):
            print('login with cookies.')
            cookies = self._load_cookies()
            self._login_with_cookies(cookies, timeout_in_seconds)
        else:
            print('login without cookies.')
            cookies = self._login_without_cookies(timeout_in_seconds)
            self._store_cookies(cookies)

    def save_share(self, share_url, timeout_in_seconds=60):
        self._browser.get(share_url)

        time.sleep(3)

        self._wait_for_element_by_xpath(WEIYUN_SAVE_BUTTON_XPATH,
                                        timeout_in_seconds)
        save_button = self._browser.find_element_by_xpath(
            WEIYUN_SAVE_BUTTON_XPATH)
        save_button.click()

        time.sleep(5)

        self._wait_for_element_by_xpath(WEIYUN_SAVE_OK_BUTTON_XPATH,
                                        timeout_in_seconds)
        ok_button = self._browser.find_element_by_xpath(
            WEIYUN_SAVE_OK_BUTTON_XPATH)
        ok_button.click()

        time.sleep(3)

    def exit(self):
        self._browser.close()

    def _load_cookies(self):
        with open(COOKIES_FILE_PATH, 'r') as fp:
            return json.load(fp)

    def _store_cookies(self, cookies):
        with open(COOKIES_FILE_PATH, 'w') as fp:
            fp.write(json.dumps(cookies))

    def _wait_for_element_by_xpath(self, xpath, timeout_in_seconds):
        WebDriverWait(self._browser, timeout_in_seconds).until(
            Expect.presence_of_element_located((By.XPATH, xpath)))

    def _login_without_cookies(self, timeout_in_seconds):
        self._browser.get('https://www.weiyun.com/')

        try:
            self._wait_for_element_by_xpath(WEIYUN_UPLOAD_BUTTON_XPATH,
                                            timeout_in_seconds)
            return self._browser.get_cookies()
        except TimeoutException:
            raise

    def _login_with_cookies(self, cookies, timeout_in_seconds):
        self._browser.get('https://www.weiyun.com/')

        self._browser.delete_all_cookies()
        for cookie in cookies:
            self._browser.add_cookie(cookie)

        time.sleep(random.random() / 2)

        self._browser.refresh()

        self._wait_for_element_by_xpath(WEIYUN_UPLOAD_BUTTON_XPATH,
                                        timeout_in_seconds)


def extract_share_urls(file_path):
    with open(file_path, 'rb') as fp:
        for line in fp:
            for url in re.findall(WEIYUN_SHARE_URL_RE_B, line, re.IGNORECASE):
                yield url.decode('latin')


def main():
    weiyun = WeiYunHelper()

    try:
        weiyun.login()
        print('weiyun login succeed.')

        urls = []
        for arg in sys.argv[1:]:
            if os.path.exists(arg):
                urls += list(extract_share_urls(arg))
            elif re.match(WEIYUN_SHARE_URL_RE, arg, re.IGNORECASE):
                urls.append(arg)
            else:
                print(
                    'Warning: {0} is neither a file nor a valid WeiYun share URL.'
                    .format(arg))

        for url in urls:
            time.sleep(random.randint(1, 3))

            print('Saving share {0} ...'.format(url))
            weiyun.save_share(url)

        print('Done. Will exit in 10 seconds.')
        time.sleep(10)

        weiyun.exit()
    except TimeoutException:
        print('weiyun login failed: timeout.')


if __name__ == '__main__':
    main()

# References:
# https://selenium-python.readthedocs.io/installation.html#downloading-selenium-server
# [selenium cookie登录](https://www.cnblogs.com/yikemogutou/p/12906145.html)
# [python模拟点击网页按钮实现方法](https://cloud.tencent.com/developer/article/1743469)
# [Wait until page is loaded with Selenium WebDriver for Python](https://stackoverflow.com/questions/26566799/wait-until-page-is-loaded-with-selenium-webdriver-for-python)
# [Open web in new tab Selenium + Python](https://stackoverflow.com/questions/28431765/open-web-in-new-tab-selenium-python)
# [python-selenium-open-tab.md](https://gist.github.com/lrhache/7686903)
