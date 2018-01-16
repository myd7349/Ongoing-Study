#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2018-01-16T10:12+08:00

__version__ = 'v0.1.0'


import os
import os.path
import re
import urllib.request

import docopt  # pip install docopt

import uriutils


__doc__ = """MIT-BIH Arrhythmia Database downloader.

Usage:
    {0} -d=<PATH>
    {0} -h | --help
    {0} -v | --version

Options:
    -d=<PATH>     Specify target directory.
    -h --help     Show this usage.
    -v --version  Show version.

""".format(os.path.basename(__file__))


def main():
    args = docopt.docopt(__doc__, version=__version__)
    target_dir = args['-d']
    
    if os.path.isfile(target_dir):
        raise SystemExit("'{0}' is supposed to be a directory.")
        
    if not os.path.isabs(target_dir):
        target_dir = os.path.join(os.getcwd(), target_dir)
        
    if not os.path.exists(target_dir):
        os.makedirs(target_dir)
    
    mitdb_url = 'https://physionet.org/physiobank/database/mitdb/'
    record_name_re = r'\d{3}\.((atr)|(dat)|(hea))'
    
    page_contents = uriutils.fetch_page_contents(mitdb_url)
    records = (rn for rn in uriutils.iurl(page_contents) if re.match(record_name_re, rn))
    record_urls = {rn: mitdb_url + rn for rn in records}
    
    for rn, rurl in record_urls.items():
        print("Downloading '{0}' from {1} ...".format(rn, rurl))
        target_file = os.path.join(target_dir, rn)
        urllib.request.urlretrieve(rurl, target_file)
        print("File '{0}' is saved as '{1}'.".format(rn, target_file))


if __name__ == '__main__':
    main()


# References:
# https://stackoverflow.com/questions/273192/how-can-i-create-a-directory-if-it-does-not-exist
