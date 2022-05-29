#!/usr/bin/env python3
# coding: utf-8

import numpy.fft

data = [1] * 8

result = numpy.fft.fft(data)
print(result)

result = numpy.fft.fft(data, norm='forward')
print(result)


# References:
# [频谱分析-FFT之后的那些事情](https://blog.csdn.net/czyt1988/article/details/84995295)
# https://github.com/czyt1988/DataProcess/blob/master/czy/signal.py
# [FFT normalization with numpy](https://stackoverflow.com/questions/39269804/fft-normalization-with-numpy)
# [Am I supposed to normalize FFT in Python?](https://dsp.stackexchange.com/questions/66058/am-i-supposed-to-normalize-fft-in-python)
