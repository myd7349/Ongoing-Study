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
from selenium.common.exceptions import TimeoutException, WebDriverException

try:
    import webdriver_manager  # pip install webdriver-manager
    del webdriver_manager
    webdriver_manager_available = True
except (ModuleNotFoundError, ImportError):
    webdriver_manager_available = False

import weiyun_config


class WeiYunHelper:
    def __init__(self, config):
        self._config = config
        self._cookies_file_path = weiyun_config.get_cookies_file_path(
            self._config)
        self._init_driver()

    def login(self, timeout_in_seconds=300):
        if os.path.exists(self._cookies_file_path):
            print('login with cookies.')
            cookies = self._load_cookies()
            self._login_with_cookies(cookies, timeout_in_seconds)
        else:
            print('login without cookies.')
            cookies = self._login_without_cookies(timeout_in_seconds)

        self._store_cookies(cookies)

        self._saved_urls = set()

    def save_share(self, share_url, timeout_in_seconds=60):
        if share_url in self._saved_urls:
            print('Share url {0} already handled.'.format(share_url))
            return

        self._browser.get(share_url)

        time.sleep(3)

        self._wait_for_element_by_xpath(weiyun_config.WEIYUN_SAVE_BUTTON_XPATH,
                                        timeout_in_seconds)
        save_button = self._browser.find_element_by_xpath(
            weiyun_config.WEIYUN_SAVE_BUTTON_XPATH)
        save_button.click()

        time.sleep(5)

        self._wait_for_element_by_xpath(
            weiyun_config.WEIYUN_SAVE_OK_BUTTON_XPATH, timeout_in_seconds)
        ok_button = self._browser.find_element_by_xpath(
            weiyun_config.WEIYUN_SAVE_OK_BUTTON_XPATH)
        ok_button.click()

        self._saved_urls.add(share_url)

        time.sleep(3)

    def exit(self):
        self._browser.close()

    def _init_driver(self):
        if self._config.browser not in weiyun_config.KNOWN_BROWSERS:
            raise RuntimeError('Unknown browser: {0}.'.format(
                self._config.browser))

        print('Browser:', self._config.browser)

        if self._config.browser_driver_path and os.path.isdir(
                self._config.browser_driver_path):
            print('Browser driver searching path: {0}.'.format(
                self._config.browser_driver_path))
            sys.path.append(self._config.browser_driver_path)

        if self._config.browser == 'Chrome':
            driver_class = webdriver.Chrome
        elif self._config.browser == 'Edge':
            driver_class = webdriver.Edge
        elif self._config.browser == 'Firefox':
            driver_class = webdriver.Firefox
        elif self._config.browser == 'Safari':
            driver_class = webdriver.Safari
        else:
            assert False, 'Unknown browser.'

        try:
            if os.path.isfile(self._config.browser_driver_path):
                self._browser = driver_class(
                    executable_path=self._config.browser_driver_path)
            else:
                self._browser = driver_class()
        except WebDriverException:
            if webdriver_manager_available:
                self._init_driver_via_manager()
            else:
                raise

    def _init_driver_via_manager(self):
        if self._config.browser == 'Chrome':
            from webdriver_manager.chrome import ChromeDriverManager
            from webdriver_manager.utils import ChromeType
            self._browser = webdriver.Chrome(
                ChromeDriverManager(chrome_type=ChromeType.GOOGLE).install())
        elif self._config.browser == 'Edge':
            from webdriver_manager.microsoft import EdgeChromiumDriverManager
            self._browser = webdriver.Edge(
                EdgeChromiumDriverManager().install())
        elif self._config.browser == 'Firefox':
            from webdriver_manager.firefox import GeckoDriverManager
            self._browser = webdriver.Firefox(
                executable_path=GeckoDriverManager().install())
        elif self._config.browser == 'Safari':
            raise NotImplementedError("Safari is not supported.")
        else:
            assert False, 'Unknown browser.'

    def _load_cookies(self):
        with open(self._cookies_file_path, 'r') as fp:
            return json.load(fp)

    def _store_cookies(self, cookies):
        with open(self._cookies_file_path, 'w') as fp:
            fp.write(json.dumps(cookies))

    def _wait_for_element_by_xpath(self, xpath, timeout_in_seconds):
        WebDriverWait(self._browser, timeout_in_seconds).until(
            Expect.presence_of_element_located((By.XPATH, xpath)))

    def _login_without_cookies(self, timeout_in_seconds):
        self._browser.get(weiyun_config.WEIYUN_HOMEPAGE)

        try:
            self._wait_for_element_by_xpath(
                weiyun_config.WEIYUN_UPLOAD_BUTTON_XPATH, timeout_in_seconds)
            return self._browser.get_cookies()
        except TimeoutException:
            raise

    def _login_with_cookies(self, cookies, timeout_in_seconds):
        self._browser.get(weiyun_config.WEIYUN_HOMEPAGE)

        self._browser.delete_all_cookies()
        for cookie in cookies:
            self._browser.add_cookie(cookie)

        time.sleep(random.random() / 2)

        self._browser.refresh()

        self._wait_for_element_by_xpath(
            weiyun_config.WEIYUN_UPLOAD_BUTTON_XPATH, timeout_in_seconds)


def extract_share_urls(file_path):
    with open(file_path, 'rb') as fp:
        for line in fp:
            for url in re.findall(weiyun_config.WEIYUN_SHARE_URL_RE_B, line,
                                  re.IGNORECASE):
                yield url.decode('latin')


def main():
    if os.path.exists(weiyun_config.CONFIG_FILE_PATH):
        config = weiyun_config.load(weiyun_config.CONFIG_FILE_PATH)
    else:
        config = weiyun_config.default_config()
        weiyun_config.store(config, weiyun_config.CONFIG_FILE_PATH)

    weiyun = WeiYunHelper(config)

    try:
        weiyun.login()
        print('weiyun login succeed.')
    except TimeoutException:
        print('weiyun login failed: timeout.')
        return

    urls = []
    for arg in sys.argv[1:]:
        if os.path.exists(arg):
            urls += list(extract_share_urls(arg))
        elif re.match(config.WEIYUN_SHARE_URL_RE, arg, re.IGNORECASE):
            urls.append(arg)
        else:
            print(
                'Warning: {0} is neither a file nor a valid WeiYun share URL.'.
                format(arg))

    for url in urls:
        time.sleep(random.randint(1, 3))

        print('Saving share {0} ...'.format(url))
        weiyun.save_share(url)

    print('Done.')
    time.sleep(1)
    weiyun.exit()


if __name__ == '__main__':
    main()

# References:
# https://selenium-python.readthedocs.io/installation.html#downloading-selenium-server
# [selenium cookie登录](https://www.cnblogs.com/yikemogutou/p/12906145.html)
# [python模拟点击网页按钮实现方法](https://cloud.tencent.com/developer/article/1743469)
# [Wait until page is loaded with Selenium WebDriver for Python](https://stackoverflow.com/questions/26566799/wait-until-page-is-loaded-with-selenium-webdriver-for-python)
# [Open web in new tab Selenium + Python](https://stackoverflow.com/questions/28431765/open-web-in-new-tab-selenium-python)
# [python-selenium-open-tab.md](https://gist.github.com/lrhache/7686903)
# https://github.com/SergeyPirogov/webdriver_manager
# https://github.com/ultrafunkamsterdam/undetected-chromedriver
