#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-19T16:16+08:00


import collections
import datetime
import json
import os
import os.path
import re
import urllib.error
import urllib.parse
import urllib.request

import docopt  # pip install docopt
import progressbar  # pip install progressbar2

import fileutil
import uriutils


__version__ = 'v0.1.0'


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

    def get_doc_template(self, url, re):
        return \
"""{desc}

Usage:
    {prog} """ + \
('--url=<URL> ' if not url else '') + \
('--re=<RegExp> ' if not re else '') + \
"""[--dir=<PATH>]
    {prog} -h | --help
    {prog} -v | --version

Options:
""" + \
('    --url=<URL>    Specify target URL.\n' if not url else '') + \
('    --re=<RegExp>  RE used to filter URLs.\n' if not re else '') + \
"""    --dir=<PATH>   Specify target directory [default: ./].
    -h --help      Show this usage.
    -v --version   Show version.

"""

    def get_description(self):
        return 'Resource Crawler.'
    
    def get_url(self):
        pass
    
    def get_re(self):
        pass

    def get_entity(self, rurl):
        rurl_parse_res = urllib.parse.urlparse(rurl)
        return ResourceEntity(rurl, rurl_parse_res.netloc, rurl_parse_res.path, *os.path.split(rurl_parse_res.path))

    def _get_meta_file(self, res_dir):
        assert os.path.exists(res_dir)
        return os.path.join(res_dir, 'rescrawler.metadata.json')

    def _load_meta_data(self, res_dir):
        meta_file = self._get_meta_file(res_dir)
        if not os.path.exists(meta_file):
            return

        with open(meta_file, encoding='utf-8') as fp:
            try:
                meta_data = json.load(fp)
                if isinstance(meta_data, dict):
                    return meta_data
            except json.JSONDecodeError:
                print('Failed to load meta data file.')

    def _write_meta_data(self, res_fullpath, url):
        res_dir, res_filename = os.path.split(res_fullpath)
        meta_data = self._load_meta_data(res_dir)
        if not meta_data:
            meta_data = {}

        meta_data[res_filename] = {
            'md5': fileutil.get_md5(res_fullpath),
            'size': os.stat(res_fullpath).st_size,
            'datetime': datetime.datetime.now().isoformat(),
            'url': url,
        }

        with open(self._get_meta_file(res_dir), 'w', encoding='utf-8') as fp:
            json.dump(meta_data, fp, indent=2)

    def _already_downloaded(self, res_fullpath):
        if not os.path.exists(res_fullpath):
            return False

        res_dir, res_filename = os.path.split(res_fullpath)
        meta_data = self._load_meta_data(res_dir)
        if not meta_data or res_filename not in meta_data:
            return False

        md5 = fileutil.get_md5(res_fullpath)
        size = os.stat(res_fullpath).st_size
        return md5 and meta_data[res_filename].get('md5', '') == md5 \
            and meta_data[res_filename].get('size', -1) == size

    def run(self):
        root_url = self.get_url()
        res_name_re = self.get_re()

        doc_temp = self.get_doc_template(root_url, res_name_re)
        doc = doc_temp.format(desc=self.get_description(), prog=self.prog)
        args = docopt.docopt(doc, version=self.ver)

        target_dir = args['--dir']
        root_url = root_url if root_url else args['--url']
        res_name_re = res_name_re if res_name_re else args['--re']
        
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

            target_file = os.path.join(res_dir, entity.filename)
            if self._already_downloaded(target_file):
                print("Skip '{0}'(already downloaded).".format(entity.filename))
            else:
                print("Downloading '{0}' from '{1}' ...".format(entity.filename, entity.url))
                try:
                    urllib.request.urlretrieve(entity.url, target_file, _show_progress)
                    print("File '{0}' is saved as '{1}'.".format(entity.filename, target_file))
                except urllib.error.HTTPError as e:
                    print("Failed to download file '{0}' from '{1}'.".format(entity.filename, entity.url))
                else:
                    self._write_meta_data(target_file, entity.url)


def main():
    prog = os.path.basename(__file__)
    ResourceCrawler(prog, __version__).run()


if __name__ == '__main__':
    main()


# References:
# https://stackoverflow.com/questions/273192/how-can-i-create-a-directory-if-it-does-not-exist
# https://stackoverflow.com/questions/8357098/how-can-i-check-if-a-url-is-absolute-using-python
# Ongoing-Study/python/notes/os.path.ipynb
# https://stackoverflow.com/questions/37748105/how-to-use-progressbar-module-with-urlretrieve
# http://docopt.org/
# https://github.com/docopt/docopt