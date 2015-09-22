#! /usr/bin/env python3
# -*- coding: utf-8 -*-

# 2015-09-22T10:30+08:00

import itertools

# Method 0
# The day of week determination algorithm used in Python's `datetime` module.
_DAYS_IN_MONTH = (-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31)
_DAYS_BEFORE_MONTH = (-1, 0) + tuple(itertools.accumulate(_DAYS_IN_MONTH[1:-1]))


def _is_leap_year(year):
    assert year > 0
    return (year % 4 == 0 and year % 100 != 0) or year % 400 == 0


def _days_before_year(year):
    assert year > 0
    year -= 1
    return year*365 + (year//4 - year//100) + year//400


def _days_in_month(year, month):
    assert year > 0
    assert 1 <= month <= 12
    if month == 2 and _is_leap_year(year):
        return 29
    return _DAYS_IN_MONTH[month]


def _days_before_month(year, month):
    assert year > 0
    assert 1 <= month <= 12
    return _DAYS_BEFORE_MONTH[month] + (month > 2 and _is_leap_year(year))


def ymd_to_ordinal(year, month, day):
    """Return proleptic Gregorian ordinal for the year, month and day.

    January 1 of year 1 is day 1.
    """
    assert 1 <= day <= _days_in_month(year, month)
    return _days_before_year(year) + _days_before_month(year, month) + day


def weekday(year, month, day):
    """Return day of the week of given date, where Monday == 0 ... Sunday == 6."""
    return (ymd_to_ordinal(year, month, day) + 6) % 7


# Method 1: Formula derived from Gauss's method, introduced in this wiki:
# https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week
def weekday2(Y, month, d):
    assert 1 <= month <= 12
    
    R = lambda x, y: x % y
    
    if month == 1:
        m = 11
        Y -= 1
    elif month == 2:
        m = 12
        Y -= 1
    else:
        m = (month-2) % 12

    w = sum(map(lambda x: x % 7,
                (d, int(2.6*m - 0.2), 5*R(Y,4), 4*R(Y,100), 6*R(Y,400))))
    return (w - 1) % 7


if __name__ == '__main__':
    import datetime
    import random
    import unittest

    predef_dates = (
        ((   1,  1,  1), 0), # Monday
        ((2015,  9, 22), 1), # Tuesday
        ((1999,  7,  7), 2), # Wednesday
        ((2099, 12, 24), 3), # Thursday
        ((2000,  2,  4), 4), # Friday
        ((2000,  1,  1), 5), # Saturday
        ((1989,  1,  1), 6), # Sunday
        ((2000, 12, 31), 6),
        ((1777,  4, 30), 2),
        ((1582, 10,  4), 0),
        )

    random_dates = []
    count = 0
    max_count = 100
    while True:
        year = random.randint(1, 9999)
        month = random.randint(1, 12)
        day = random.randint(0, 31)

        try:
            date = datetime.date(year, month, day)
            random_dates.append(((year, month, day), date.weekday()))
            
            count += 1
            if count == max_count:
                break
        except ValueError:
            pass

    ever_failed_dates = (
        ((1219,  4,  3), 2),
        (( 741, 11, 13), 3),
        ((9098,  3, 18), 4),
        ((7008,  9, 24), 5),
        ((1414,  8,  7), 6),
        )

    class WeekDayTestCase(unittest.TestCase):
        def _test_impl(self, method, data):
            for date, week_day in data:
                msg = '{}({}, {}, {}) == {}'.format(method.__name__, *date, week_day)
                self.assertEqual(method(*date), week_day, msg)

        def test_predef_dates(self):
            self._test_impl(weekday, predef_dates)
            self._test_impl(weekday2, predef_dates)

        def test_random_dates(self):
            self._test_impl(weekday, random_dates)
            self._test_impl(weekday2, random_dates)

        def test_ever_failed_dates(self):
            self._test_impl(weekday, ever_failed_dates)
            self._test_impl(weekday2, ever_failed_dates) 
    
    unittest.main()
