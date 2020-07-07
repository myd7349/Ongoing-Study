#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import gooey

import extract_columns


@gooey.Gooey
def main():
    extract_columns.main()


if __name__ == '__main__':
    main()
