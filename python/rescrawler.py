#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-19T16:16+08:00


import collections
import os
import os.path
import re
import urllib.parse
import urllib.request

import docopt  # pip install docopt
import progressbar  # pip install progressbar2

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


# path = join(subdir, filename)
ResourceEntity = collections.namedtuple('ResourceEntity', ['url', 'netloc', 'path', 'subdir', 'filename'])


def _mkdir(path):
    if not os.path.exists(path):
        print("Creating directory '{0}'...".format(path))
        os.makedirs(path)


_progress_bar = None

def _show_progress(block_num, block_size, total_size):
    global _progress_bar
    if _progress_bar is None:
        _progress_bar = progressbar.ProgressBar(maxval=total_size)

    downloaded = block_num * block_size
    if downloaded < total_size:
        _progress_bar.update(downloaded)
    else:
        _progress_bar.finish()
        _progress_bar = None


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

    def get_entity(self, rurl):
        rurl_parse_res = urllib.parse.urlparse(rurl)
        return ResourceEntity(rurl, rurl_parse_res.netloc, rurl_parse_res.path, *os.path.split(rurl_parse_res.path))
    
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
        
        _mkdir(target_dir)
    
        page_contents = uriutils.fetch_page_contents(root_url)
        res = (rn for rn in uriutils.iurl(page_contents) if re.match(res_name_re, rn))
        res_urls = {rn: urllib.parse.urljoin(root_url, rn) for rn in res}
    
        for rurl in res_urls.values():
            entity = self.get_entity(rurl)
            
            netloc_dir = os.path.join(target_dir, entity.netloc)
            _mkdir(netloc_dir)

            res_subdir = entity.subdir[1:] if entity.subdir.startswith('/') else entity.subdir
            res_dir = os.path.join(netloc_dir, res_subdir)
            _mkdir(res_dir)

            print("Downloading '{0}' from '{1}' ...".format(entity.filename, entity.url))
            target_file = os.path.join(res_dir, entity.filename)
            urllib.request.urlretrieve(entity.url, target_file, _show_progress)
            print("File '{0}' is saved as '{1}'.".format(entity.filename, target_file))


# References:
# https://stackoverflow.com/questions/273192/how-can-i-create-a-directory-if-it-does-not-exist
# https://stackoverflow.com/questions/8357098/how-can-i-check-if-a-url-is-absolute-using-python
# Ongoing-Study/python/notes/os.path.ipynb
# https://stackoverflow.com/questions/37748105/how-to-use-progressbar-module-with-urlretrieve
