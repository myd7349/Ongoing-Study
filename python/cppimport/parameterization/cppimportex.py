#! /usr/bin/env python3
# coding: utf-8

# 2017-01-14T20:45:51+08:00

import os


import cppimport.find
import cppimport.importer


def setup_module_data(fullname, filepath, **kwargs):
    module_data = cppimport.importer.setup_module_data(fullname, filepath)
    module_data.update(kwargs)
    return module_data


def imp(fullname, **kwargs):
    # Search through sys.path to find a file that matches the module
    filepath = cppimport.find.find_module_cpppath(fullname)

    if filepath is None or not os.path.exists(filepath):
        raise ImportError(
            "Couldn't find a file matching the module name " + str(fullname)
        )

    module_data = setup_module_data(fullname, filepath, **kwargs)
    if cppimport.importer.should_rebuild(module_data):
        cppimport.importer.template_and_build(filepath, module_data)
        return __import__(fullname)
    else:
        cppimport.importer.quiet_print("Matching checksum for " + filepath + " --> not compiling")
        try:
            return __import__(fullname)
        except ImportError as e:
            cppimport.importer.quiet_print(
                "ImportError during import with matching checksum. Trying to rebuild.")
            cppimport.importer.template_and_build(filepath, module_data)
            return __import__(fullname)
