#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-01T15:20+08:00

__author__ = 'myd7349 <myd7349@gmail.com>'
__version__ = '0.0.1'

import configparser
import odbc
import string

import dicom # [pydicom](http://www.pydicom.org/)

db_section = 'DB'
db_options = ('DRIVER', 'SERVER', 'PORT', 'DATABASE', 'DBQ', 'UID', 'PWD', 'CaseTable', 'DataTable')
fields_section = 'Fields'
fields_options = (
    'AdditionalPatientHistory',
    'InstitutionAddress',
    'InstitutionalDepartmentName',
    'InstitutionName',
    'Manufacturer',
    'PatientAge',
    'PatientBirthDate',
    'PatientID',
    'PatientName',
    'PatientSex',
    'PatientSize',
    'PatientWeight',
    'ReferringPhysicianName',
    'SoftwareVersions',
    'StudyDate',
    'StudyTime',
    )

def read_config_file(config_file, config_dict = {}):
    '''Load configuration information from specified file.
    If the file doesn't exist, create a configuration template, which you should
    edit manually first to make it a useful one.
    '''
    config = configparser.ConfigParser()
    config.optionxform = str
    config.read(config_file)

    need_to_init = False

    vsections = db_section, fields_section
    voptions = db_options, fields_options

    for section, options in zip(vsections, voptions):
        if section not in config:
            config[section] = {}
            need_to_init = True

        for option in options:
            if option not in config[section]:
                config[section][option] = ''
                need_to_init = True

    config_dict_2 = {section: v for section, v in config_dict if section in config}
    for section in config_dict_2.keys():
        for option in config_dict_2[section].keys():
            if option not in config[section]:
                config_dict_2[section].pop(option)
    config.read_dict(config_dict_2)
    
    if need_to_init:
        with open(config_file, 'w') as fp:
            config.write(fp)
        return

    return config

def _create_connection_string(config):
    if not config[db_section]['DRIVER']:
        raise ValueError('"DRIVER" not provided')

    temp = string.Template('$arg={0[$arg]};')
    args = ['DRIVER']

    if config[db_section]['DBQ']:
        args.append('DBQ') # For databases like Microsoft Access's mdb file on local disk
    else:
        if not all(map(bool, (config[db_section]['SERVER'],
                              config[db_section]['PORT'],
                              config[db_section]['DATABASE']))):
            raise ValueError('''Make sure that one of this condition is satisfied: 1. "DBQ" is provided; 2. "SERVER", "PORT", "DATABASE" are all provided''')
        args += ['SERVER', 'PORT', 'DATABASE'] # For databases like MySql on remote server

    args += ['UID', 'PWD']
    return ''.join(map(lambda x: temp.substitute(arg = x), args)).format(config[db_section])

def fetch_patient_info(config_file, config_dict = {}, projection = {}):
    config = read_config_file(config_file, config_dict)
    if not config:
        raise RuntimeError('Failed to load configuration file.')

    conn_str = _create_connection_string(config)
    if __debug__:
        print(conn_str)

    connection = odbc.odbc(conn_str)
    try:
        cursor = connection.cursor()
        cursor.execute('')
    finally:
        connection.close()
    
if __name__ == '__main__':
    fetch_patient_info(r'd:\1.cfg')

# References:
# [MS Access library for python](http://stackoverflow.com/questions/1047580/ms-access-library-for-python)
# [Microsoft Access ODBC Driver connection strings](https://www.connectionstrings.com/microsoft-access-odbc-driver/)
# [Preserve case in ConfigParser?](http://stackoverflow.com/questions/1611799/preserve-case-in-configparser)
