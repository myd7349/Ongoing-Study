#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 2014-12-12T09:38+08:00

import configparser
import os.path

import azure.storage

config_file = os.path.splitext(__file__)[0] + '.cfg'
config_parser = configparser.ConfigParser()

section = 'ACCOUNT'
name_option = 'name'
key_option = 'key'
host_option = 'host'

# The structure of the configuration file:
'''
[ACCOUNT]
name = Your account name here. Note that it is not your Azure login name.
key = Your account key here. Note that it is not your Azure login password.
host = Your host base here. For example, I am using Microsoft Azure China, so I use .blob.core.chinacloudapi.cn as the host base.
'''
config_parser.read(config_file, encoding = 'utf-8')
if not config_parser.has_section(section):
    raise ValueError('Invalid configuration file. Section "{}" doesn\'t exist.'.format(section))
if not config_parser.has_option(section, name_option) or not config_parser.has_option(section, key_option):
    raise ValueError('Invalid configuration file. Option "{}" or "{}" is not found under section "{}".'
                     .format(name_option, key_option, section))

def main():
    # get account name
    name = config_parser[section][name_option]

    # get account key
    key = config_parser[section][key_option]
    
    # get host_base
    host = '.blob.core.windows.net' # The default value of host_base in BlobService.__init__
    # Note that the official Azure storage tutorial for Python in this page:
    # http://www.windowsazure.cn/zh-cn/develop/python/how-to-guides/blob-service/
    # doesn't mention about the 'host_base' keyword argument in BlobService.__init__.
    # However, for those who are not using the <Microsoft Azure Default>, it is
    # important to specify this parameter explicitly.
    # For example, I am using the <Microsoft Azure China>, so I should pass:
    # .blob.core.chinacloudapi.cn
    # to 'host_base'.
    # This idea is inspired by the Azure Storage Explorer(http://azurestorageexplorer.codeplex.com/).
    # When I launched this application, it gave me an option to specify the Azure host.
    if config_parser.has_option(section, host_option) and config_parser[section][host_option].strip():
        host = config_parser[section][host_option]
        
    blob_service = azure.storage.BlobService(account_name = name, account_key = key, host_base = host)
    blob_service.create_container('myd7349')

if __name__ == '__main__':
    main()
