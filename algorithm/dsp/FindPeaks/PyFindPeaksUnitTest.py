#! /usr/bin/env python3
# -*- coding: utf-8 -*-

import random
import unittest

import numpy as np

import PyFindPeaksEx
import detect_peaks


class TestFindPeaks(unittest.TestCase):
    def do_test(self, **kwargs):
        x = np.random.randn(1000)
        x[600:801] = np.nan

        peaks1 = PyFindPeaksEx.find_peaks(x, **kwargs)
        peaks2 = detect_peaks.detect_peaks(x, **kwargs)

        self.assertTrue(np.array_equal(peaks1, peaks2))

    def test_default(self):
        self.do_test()

    def test_mph(self):
        self.do_test(mph=random.uniform(0.25, 2.5))
        
    def test_mpd(self):
        self.do_test(mpd=random.randint(1, 100))

    def test_threshold(self):
        self.do_test(threshold=random.uniform(0.25, 5))

    def test_edge_none(self):
        self.do_test(edge=None)

    def test_edge_falling(self):
        self.do_test(edge='falling')

    def test_edge_both(self):
        self.do_test(edge='both')

    def test_kpsh(self):
        self.do_test(kpsh=True)

    def test_valley(self):
        self.do_test(valley=True)

    def test_all(self):
        self.do_test(
            mph=random.uniform(0.25, 2.5),
            mpd=random.randint(1, 100),
            threshold=random.uniform(0.25, 5),
            edge=random.choice((None, 'falling', 'rising', 'both')),
            kpsh=random.choice((True, False)),
            valley=random.choice((True, False)))


if __name__ == '__main__':
    unittest.main()
