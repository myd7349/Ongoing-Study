#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-06-01T15:20+08:00

__author__ = 'myd7349 <myd7349@gmail.com>'
__version__ = '0.0.3'

import collections
import configparser
import contextlib
try:
    import odbc
except ImportError:
    # Since Python 3.5, the builtin module `odbc` is removed.
    # Thanks to PEP 0249, I can use a 3rdparty library `pyodbc`
    # here without touching the original code.
    import pyodbc as odbc
    odbc.odbc = odbc.connect
import re
import string

import dicom  # [pydicom](http://www.pydicom.org/)

import fileutil


db_section = 'DB'
db_options = ('DRIVER', 'SERVER', 'PORT', 'DATABASE', 'DBQ', 'UID', 'PWD')
fields_section = 'Fields'
fields_options = (
    'AdditionalPatientHistory',
    'AdmittingDiagnosesDescription',
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

table_field_re = re.compile(r'(?P<table>\w+).(?P<field>\w+)')
table_field_re_strict = re.compile(r'^(?P<table>\w+).(?P<field>\w+)$')


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


def _create_single_sql_statement(mapped_fields, tables, query_criteria):
    sql = ''
    keywords = []

    keyword_field_map = collections.OrderedDict()
    for table in tables:
        keyword_field_map.update(mapped_fields[table])

    if keyword_field_map:
        keywords = list(keyword_field_map.keys())
        
        formatter = '{{0[{}]}}'.format
        sql = 'SELECT ' + ', '.join(map(formatter, keywords)) + \
              ' FROM ' + ', '.join(tables) + \
              (' WHERE ' + query_criteria if query_criteria else '')
        sql = sql.format(keyword_field_map)

    return sql, keywords


def _create_sql_statements(config, info_from_db, criteria_arg):
    sqls = []
    keywords_array = []

    if not info_from_db:
        return sqls, keywords
    
    tables_used_in_criteria = {matched_res.group('table')
                               for matched_res in table_field_re.finditer(
                                   ' '.join([config[query_section]['Criteria'],
                                             config[query_section]['CriteriaWithOneArg']]))}
    tables = {value.split('.')[0] for value in info_from_db.values()}
    tables_has_relationship = tables.intersection(tables_used_in_criteria)
    tables_standardalone = tables - tables_has_relationship

    mapped_fields = {}
    for keyword, value in info_from_db.items():
        table = value.split('.')[0]
        if table not in mapped_fields:
            mapped_fields[table] = {}
        mapped_fields[table][keyword] = value

    
    if tables_has_relationship:
        criteria = config[query_section]['Criteria']
        criteria_with_1arg = config[query_section]['CriteriaWithOneArg'].format(criteria_arg) \
                             if config[query_section]['CriteriaWithOneArg'] and criteria_arg else ''
        criteria += (' and ' if criteria and criteria_with_1arg else '') + criteria_with_1arg

        sql_, keywords_ = _create_single_sql_statement(mapped_fields, tables_has_relationship, criteria)
        if sql_ and keywords_:
            sqls.append(sql_)
            keywords_array.append(keywords_)

    for table in tables_standardalone:
        sql_, keywords_ = _create_single_sql_statement(mapped_fields, (table, ), None)
        if sql_ and keywords_:
            sqls.append(sql_)
            keywords_array.append(keywords_)

    return sqls, keywords_array


def _read_config_file(config_file, config_dict=None, extra_elems_dict=None):
    if config_dict is None:
        config_dict = {}

    if extra_elems_dict is None:
        extra_elems_dict = {}

    config = configparser.ConfigParser()
    config.optionxform = str
    encoding = fileutil.get_file_encoding(config_file)
    # Load configuration information from specified file.
    config.read(config_file, encoding=encoding)

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

    config_dict = {section: config_dict[section] for section in config_dict if section in config}
    for section in config_dict:
        for option in config_dict[section]:
            if option not in config[section]:
                config_dict[section].pop(option)
    config.read_dict(config_dict)

    if need_to_init:
        # If the configuration file doesn't exist, create a configuration
        # template, which you should edit manually first to make it a useful one.
        with open(config_file, 'w', encoding=encoding) as fp:
            config.write(fp)
    else:
        config[fields_section].update(extra_elems_dict)
        return config


def _correct_value(keyword, value):
    # Correct the type of the value. For example, the PatientAge's VR is 'AS'(that is, a string).
    # However, the PatientAge information we got from database maybe an integer. In this case,
    # we should convert this integer into a string first. Otherwise, pydicom's filewriter module
    # will raise a TypeError exception.
    empty_value = {bytes: b'', float: 0.0, int: 0, str: ''}
    # TODO: More VRs handling
    # TODO: Try to normalize VRs like AS, DT according to PS3.5 6.2
    VR_type_map = {
        'AS': str,
        'DA': str,
        'DS': str,
        'DT': str,
        'IS': str,
        'LO': str,
        'LT': str,
        }
    VR = dicom.dataset.dictionaryVR(dicom.dataset.tag_for_name(keyword))
    if VR in VR_type_map:
        if value is None:
            return empty_value[VR_type_map[VR]]
        else:
            return VR_type_map[VR](value)

    return value


def fetch_patient_info(config_file, config_dict=None, extra_elems_dict=None, criteria_arg=''):
    """Fetch patient information from various source(configuration files, database) with a
    user-defined behavior.
    
    config_file: Configuration file name.
    config_dict: This dictionary is used to initialize the configparser.ConfigParser
                 object. You can use this arguement to specify initial value of those
                 keywords listed in `fields_options`.
    extra_elems_dict: Specify additional elements that are not existing in `fields_options`.
    criteria_arg: Criteria argument used to generate SQL statement.
    """
    config = _read_config_file(config_file, config_dict, extra_elems_dict)
    if not config:
        raise RuntimeError('Failed to load configuration file')

    cached_cfg_parsers = {}

    def get_value_from_cfg(*, file, encoding, section, option):
        if file not in cached_cfg_parsers:
            config_parser = configparser.ConfigParser()
            config_parser.optionxform = str
            config_parser.read(file, encoding=encoding if encoding else fileutil.get_file_encoding(file))
            cached_cfg_parsers[file] = config_parser
        return cached_cfg_parsers[file][section][option]
    
    ds = dicom.dataset.Dataset()

    info_res = []
    info_callbacks = []
    # The format of configuration information can be one of these three forms:
    # 1. Raw information(enclosed by square brackets);
    info_res.append(re.compile(r'^\[(.+)\]$'))
    info_callbacks.append(lambda keyword, matched_res: setattr(ds, keyword, matched_res.group(1)))
    # 2. Information that comes from a INI-likely configuration file(consist of four parts);
    info_res.append(re.compile(r'''
                                ^(?P<file>.+?)          # Part 1: configuration file path
                                (?:\|(?P<encoding>.+))? # Part 2(if exists): the encoding of the configuration file
                                \[(?P<section>.+)\]     # Part 3: a section name enclosed by square brackets
                                (?P<option>.+)$         # Part 4: option name
                                ''', re.VERBOSE))
    info_callbacks.append(lambda keyword, matched_res: setattr(ds, keyword, get_value_from_cfg(**matched_res.groupdict())))
    # 3. Information that comes from a database(table name and field name are split by a dot);
    info_res.append(table_field_re_strict)
    info_from_db = dict()
    info_callbacks.append(lambda keyword, matched_res: info_from_db.update({keyword: matched_res.group()}))
    
    for keyword in config[fields_section]:
        value = config[fields_section][keyword]
        if value:
            for compiled_re, callback in zip(info_res, info_callbacks):
                matched_res = compiled_re.match(value)
                if matched_res:
                    callback(keyword, matched_res)

    debug_print = lambda *args, **kwargs: print(*args, **kwargs) if __debug__ else None
    
    # Fetch patient information from database
    conn_str = _create_connection_string(config)
    debug_print(conn_str)

    with contextlib.closing(odbc.odbc(conn_str)) as connection:
        with contextlib.closing(connection.cursor()) as cursor:
            for sql, keywords in zip(*_create_sql_statements(config, info_from_db, criteria_arg)):
                debug_print(sql)
                debug_print(keywords)
                if sql and keywords:
                    cursor.execute(sql)
                    record = cursor.fetchone()
                    if record:
                        for keyword, value in zip(keywords, record):
                            setattr(ds, keyword, _correct_value(keyword, value))
    
    debug_print(ds)
    return ds


if __name__ == '__main__':    
    dataset = fetch_patient_info(r'testdb.configuration', criteria_arg='0002', extra_elems_dict={})

# References:
# [MS Access library for python](http://stackoverflow.com/questions/1047580/ms-access-library-for-python)
# [Microsoft Access ODBC Driver connection strings](https://www.connectionstrings.com/microsoft-access-odbc-driver/)
# [Preserve case in ConfigParser?](http://stackoverflow.com/questions/1611799/preserve-case-in-configparser)
