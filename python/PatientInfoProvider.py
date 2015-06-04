#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-01T15:20+08:00

__author__ = 'myd7349 <myd7349@gmail.com>'
__version__ = '0.0.1'

import configparser
import odbc
import re
import string

import dicom  # [pydicom](http://www.pydicom.org/)

db_section = 'DB'
db_options = ('DRIVER', 'SERVER', 'PORT', 'DATABASE', 'DBQ', 'UID', 'PWD')
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
query_section = 'Query'
query_options = ('Criteria', 'CriteriaWithOneArg')


def _create_connection_string(config):
    if not config[db_section]['DRIVER']:
        raise ValueError('"DRIVER" not provided')

    temp = string.Template('$arg={0[$arg]};')
    args = ['DRIVER']

    if config[db_section]['DBQ']:
        args.append('DBQ')  # For databases like Microsoft Access's mdb file on local disk
    else:
        if not all(map(bool, (config[db_section]['SERVER'],
                              config[db_section]['PORT'],
                              config[db_section]['DATABASE']))):
            raise ValueError('Make sure that one of this condition is satisfied: '
                             '1. "DBQ" is provided; '
                             '2. "SERVER", "PORT", "DATABASE" are all provided')
        args += ['SERVER', 'PORT', 'DATABASE']  # For databases like MySql on remote server

    args += ['UID', 'PWD']

    return ''.join(map(lambda x: temp.substitute(arg=x), args)).format(config[db_section])


def _get_nonempty_options(config):
    return [key for key in config[fields_section] if config[fields_section][key]]


def _create_sql_statement(config, criteria_arg):
    sql = ''
    nonempty_options = _get_nonempty_options(config)
    mapped_field = {}
    tables = set()

    for option in nonempty_options:
        try:
            table, field = re.split('[,;:.]', config[fields_section][option])
            table_field = '{}.{}'.format(table, field)
            mapped_field[option] = table_field
            tables.add(table)
        except ValueError:
            raise ValueError('Invalid format to map "{}" to a specified table field in a database. The '
                             'accepted format is: [table name][spliter][field name]. The splitter can be '
                             'one of [,;:.]'.format(option))

    if nonempty_options and tables:
        query_criteria = config[query_section]['Criteria']
        additional_criteria = config[query_section]['CriteriaWithOneArg'].format(criteria_arg) \
            if config[query_section]['CriteriaWithOneArg'] and criteria_arg else ''

        query_criteria += (' and ' if query_criteria and additional_criteria else '') + additional_criteria

        sql = 'SELECT ' + ', '.join('{{0[{}]}}'.format(option) for option in nonempty_options) + \
              ' FROM ' + ', '.join(tables) + \
              (' WHERE ' if query_criteria else '') + query_criteria
        sql = sql.format(mapped_field)

    return sql


def _debug_print(*args, **kwargs):
    if __debug__:
        print(*args, **kwargs)


def read_config_file(config_file, config_dict=None):
    """Load configuration information from specified file.
    If the file doesn't exist, create a configuration template, which you should
    edit manually first to make it a useful one.
    """
    if config_dict is None:
        config_dict = {}

    config = configparser.ConfigParser()
    config.optionxform = str
    config.read(config_file, encoding='utf-8')

    need_to_init = False

    vsections = db_section, fields_section, query_section
    voptions = db_options, fields_options, query_options

    for section, options in zip(vsections, voptions):
        if section not in config:
            config[section] = {}
            need_to_init = True
        for option in options:
            if option not in config[section]:
                config[section][option] = ''
                need_to_init = True

    config_dict = {section: v for section, v in config_dict if section in config}
    for section in config_dict.keys():
        for option in config_dict[section].keys():
            if option not in config[section]:
                config_dict[section].pop(option)
    config.read_dict(config_dict)

    if need_to_init:
        with open(config_file, 'w') as fp:
            config.write(fp)
        return

    return config


def fetch_patient_info(config_file, config_dict=None, criteria_arg=''):
    config = read_config_file(config_file, config_dict)
    if not config:
        raise RuntimeError('Failed to load configuration file.')

    conn_str = _create_connection_string(config)
    _debug_print(conn_str)

    connection = odbc.odbc(conn_str)
    ds = dicom.dataset.Dataset()

    try:
        cursor = connection.cursor()

        sql = _create_sql_statement(config, criteria_arg)
        _debug_print(sql)

        if sql:
            cursor.execute(sql)
            try:
                for attr, val in zip(_get_nonempty_options(config), cursor.fetchone()):
                    setattr(ds, attr, val)
            finally:
                pass
    finally:
        connection.close()

    assert isinstance(ds, dicom.dataset.Dataset)
    return ds


if __name__ == '__main__':
    file_meta = fetch_patient_info(r'testdb.configuration', criteria_arg='0002')
    print(file_meta)

# References:
# [MS Access library for python](http://stackoverflow.com/questions/1047580/ms-access-library-for-python)
# [Microsoft Access ODBC Driver connection strings](https://www.connectionstrings.com/microsoft-access-odbc-driver/)
# [Preserve case in ConfigParser?](http://stackoverflow.com/questions/1611799/preserve-case-in-configparser)
