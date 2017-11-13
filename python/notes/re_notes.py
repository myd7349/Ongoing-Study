#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2016-08-13T23:28+08:00

# From Chromium depo tools/scm.py
def ValidateEmail(email):
  return (re.match(r"^[a-zA-Z0-9._%-+]+@[a-zA-Z0-9._%-]+.[a-zA-Z]{2,6}$", email)
          is not None)
