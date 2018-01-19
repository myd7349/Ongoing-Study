#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-19T16:16+08:00


import os
import os.path
import re
import urllib.request

import docopt  # pip install docopt

import uriutils


doc_temp = """{desc}

Usage:
    {prog} -d=<PATH>
    {prog} -h | --help
    {prog} -v | --version

Options:
    -d=<PATH>     Specify target directory.
    -h --help     Show this usage.
    -v --version  Show version.

"""


class ResourceCrawler:
    def __init__(self, prog, ver):
        self.prog = prog
        self.ver = ver

    def get_description(self):
        pass
    
    def get_url(self):
        pass
    
    def get_re(self):
        pass
    
    def run(self):
        doc = doc_temp.format(desc=self.get_description(), prog=self.prog)
        args = docopt.docopt(doc, version=self.ver)
        target_dir = args['-d']
        
        root_url = self.get_url()
        assert root_url is not None, 'Invalid root url.'
        
        res_name_re = self.get_re()
        assert res_name_re is not None, 'Invalid RE.'
        
        if os.path.isfile(target_dir):
            raise SystemExit("'{0}' is supposed to be a directory.")
        
        if not os.path.isabs(target_dir):
            target_dir = os.path.join(os.getcwd(), target_dir)
        
        if not os.path.exists(target_dir):
            os.makedirs(target_dir)
    
        page_contents = uriutils.fetch_page_contents(root_url)
        res = (rn for rn in uriutils.iurl(page_contents) if re.match(res_name_re, rn))
        res_urls = {rn: root_url + rn for rn in res}
    
        for rn, rurl in res_urls.items():
            print("Downloading '{0}' from {1} ...".format(rn, rurl))
            target_file = os.path.join(target_dir, rn)
            urllib.request.urlretrieve(rurl, target_file)
            print("File '{0}' is saved as '{1}'.".format(rn, target_file))


# References:
# https://stackoverflow.com/questions/273192/how-can-i-create-a-directory-if-it-does-not-exist
