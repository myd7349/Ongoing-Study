#!/usr/bin/env python3
# coding: utf-8

import matplotlib.pyplot as plt
import numpy as np


def generate_wave(fs, n):
    t = np.arange(n, dtype=float) / fs
    wave = 1 * np.cos(2 * np.pi * 10 * t) + \
        2 * np.sin(2 * np.pi * 15 * t + np.deg2rad(30)) + \
        3 * np.cos(2 * np.pi * 20 * t + np.deg2rad(-30)) + \
        4 * np.sin(2 * np.pi * 26.5 * t + np.deg2rad(60))

    print(wave)
    return t, wave


def main():
    fs = 100
    n = 256

    t, wave = generate_wave(fs, n)
    print(wave)

    plt.subplot(3, 1, 1)
    plt.plot(t, wave)
    plt.title('Data')

    Y = np.fft.fft(wave)
    print(Y)

    plt.subplot(3, 1, 2)
    #plt.plot(abs(Y))
    plt.plot(np.abs(Y))

    plt.show()


if __name__ == '__main__':
    main()


# References:
# [傅里叶分析之掐死教程（完整版）更新于2014.06.06](https://zhuanlan.zhihu.com/p/19763358)
# [频谱分析-FFT之后的那些事情](https://blog.csdn.net/czyt1988/article/details/84995295)
# https://github.com/czyt1988/DataProcess/blob/master/czy/signal.py
