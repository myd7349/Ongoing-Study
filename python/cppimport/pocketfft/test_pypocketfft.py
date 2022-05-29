# https://github.com/numpy/numpy/blob/main/numpy/fft/tests/test_pocketfft.py
# License: https://github.com/numpy/numpy/blob/main/LICENSE.txt
# !pytest test_pypocketfft.py

import numpy as np
import pytest
from numpy.random import random
from numpy.testing import (
        assert_array_equal, assert_raises, assert_allclose
        )
import threading
import queue

import pypocketfft


def fft1(x):
    L = len(x)
    phase = -2j * np.pi * (np.arange(L) / L)
    phase = np.arange(L).reshape(-1, 1) * phase
    return np.sum(x*np.exp(phase), axis=1)


class TestFFTShift:

    def test_fft_n(self):
        assert_raises(ValueError, pypocketfft.fft, [1, 2, 3], 0)


class TestFFT1D:

    def test_identity(self):
        maxlen = 512
        x = random(maxlen) + 1j*random(maxlen)
        xr = random(maxlen)
        for i in range(1, maxlen):
            assert_allclose(pypocketfft.ifft(pypocketfft.fft(x[0:i])), x[0:i],
                            atol=1e-12)
            assert_allclose(pypocketfft.irfft(pypocketfft.rfft(xr[0:i]), i),
                            xr[0:i], atol=1e-12)

    def test_fft(self):
        x = random(30) + 1j*random(30)
        assert_allclose(fft1(x), pypocketfft.fft(x), atol=1e-6)
        assert_allclose(fft1(x), pypocketfft.fft(x, norm="backward"), atol=1e-6)
        assert_allclose(fft1(x) / np.sqrt(30),
                        pypocketfft.fft(x, norm="ortho"), atol=1e-6)
        assert_allclose(fft1(x) / 30.,
                        pypocketfft.fft(x, norm="forward"), atol=1e-6)

    @pytest.mark.parametrize('norm', (None, 'backward', 'ortho', 'forward'))
    def test_ifft(self, norm):
        x = random(30) + 1j*random(30)
        assert_allclose(
            x, pypocketfft.ifft(pypocketfft.fft(x, norm=norm), norm=norm),
            atol=1e-6)
        # Ensure we get the correct error message
        with pytest.raises(ValueError,
                           match='Invalid number of FFT data points'):
            pypocketfft.ifft([], norm=norm)

    def test_fft2(self):
        x = random((30, 20)) + 1j*random((30, 20))
        assert_allclose(pypocketfft.fft(pypocketfft.fft(x, axis=1), axis=0),
                        pypocketfft.fft2(x), atol=1e-6)
        assert_allclose(pypocketfft.fft2(x),
                        pypocketfft.fft2(x, norm="backward"), atol=1e-6)
        assert_allclose(pypocketfft.fft2(x) / np.sqrt(30 * 20),
                        pypocketfft.fft2(x, norm="ortho"), atol=1e-6)
        assert_allclose(pypocketfft.fft2(x) / (30. * 20.),
                        pypocketfft.fft2(x, norm="forward"), atol=1e-6)

    def test_ifft2(self):
        x = random((30, 20)) + 1j*random((30, 20))
        assert_allclose(pypocketfft.ifft(pypocketfft.ifft(x, axis=1), axis=0),
                        pypocketfft.ifft2(x), atol=1e-6)
        assert_allclose(pypocketfft.ifft2(x),
                        pypocketfft.ifft2(x, norm="backward"), atol=1e-6)
        assert_allclose(pypocketfft.ifft2(x) * np.sqrt(30 * 20),
                        pypocketfft.ifft2(x, norm="ortho"), atol=1e-6)
        assert_allclose(pypocketfft.ifft2(x) * (30. * 20.),
                        pypocketfft.ifft2(x, norm="forward"), atol=1e-6)

    def test_fftn(self):
        x = random((30, 20, 10)) + 1j*random((30, 20, 10))
        assert_allclose(
            pypocketfft.fft(pypocketfft.fft(pypocketfft.fft(x, axis=2), axis=1), axis=0),
            pypocketfft.fftn(x), atol=1e-6)
        assert_allclose(pypocketfft.fftn(x),
                        pypocketfft.fftn(x, norm="backward"), atol=1e-6)
        assert_allclose(pypocketfft.fftn(x) / np.sqrt(30 * 20 * 10),
                        pypocketfft.fftn(x, norm="ortho"), atol=1e-6)
        assert_allclose(pypocketfft.fftn(x) / (30. * 20. * 10.),
                        pypocketfft.fftn(x, norm="forward"), atol=1e-6)

    def test_ifftn(self):
        x = random((30, 20, 10)) + 1j*random((30, 20, 10))
        assert_allclose(
            pypocketfft.ifft(pypocketfft.ifft(pypocketfft.ifft(x, axis=2), axis=1), axis=0),
            pypocketfft.ifftn(x), atol=1e-6)
        assert_allclose(pypocketfft.ifftn(x),
                        pypocketfft.ifftn(x, norm="backward"), atol=1e-6)
        assert_allclose(pypocketfft.ifftn(x) * np.sqrt(30 * 20 * 10),
                        pypocketfft.ifftn(x, norm="ortho"), atol=1e-6)
        assert_allclose(pypocketfft.ifftn(x) * (30. * 20. * 10.),
                        pypocketfft.ifftn(x, norm="forward"), atol=1e-6)

    def test_rfft(self):
        x = random(30)
        for n in [x.size, 2*x.size]:
            for norm in [None, 'backward', 'ortho', 'forward']:
                assert_allclose(
                    pypocketfft.fft(x, n=n, norm=norm)[:(n//2 + 1)],
                    pypocketfft.rfft(x, n=n, norm=norm), atol=1e-6)
            assert_allclose(
                pypocketfft.rfft(x, n=n),
                pypocketfft.rfft(x, n=n, norm="backward"), atol=1e-6)
            assert_allclose(
                pypocketfft.rfft(x, n=n) / np.sqrt(n),
                pypocketfft.rfft(x, n=n, norm="ortho"), atol=1e-6)
            assert_allclose(
                pypocketfft.rfft(x, n=n) / n,
                pypocketfft.rfft(x, n=n, norm="forward"), atol=1e-6)

    def test_irfft(self):
        x = random(30)
        assert_allclose(x, pypocketfft.irfft(pypocketfft.rfft(x)), atol=1e-6)
        assert_allclose(x, pypocketfft.irfft(pypocketfft.rfft(x, norm="backward"),
                        norm="backward"), atol=1e-6)
        assert_allclose(x, pypocketfft.irfft(pypocketfft.rfft(x, norm="ortho"),
                        norm="ortho"), atol=1e-6)
        assert_allclose(x, pypocketfft.irfft(pypocketfft.rfft(x, norm="forward"),
                        norm="forward"), atol=1e-6)

    def test_rfft2(self):
        x = random((30, 20))
        assert_allclose(pypocketfft.fft2(x)[:, :11], pypocketfft.rfft2(x), atol=1e-6)
        assert_allclose(pypocketfft.rfft2(x),
                        pypocketfft.rfft2(x, norm="backward"), atol=1e-6)
        assert_allclose(pypocketfft.rfft2(x) / np.sqrt(30 * 20),
                        pypocketfft.rfft2(x, norm="ortho"), atol=1e-6)
        assert_allclose(pypocketfft.rfft2(x) / (30. * 20.),
                        pypocketfft.rfft2(x, norm="forward"), atol=1e-6)

    def test_irfft2(self):
        x = random((30, 20))
        assert_allclose(x, pypocketfft.irfft2(pypocketfft.rfft2(x)), atol=1e-6)
        assert_allclose(x, pypocketfft.irfft2(pypocketfft.rfft2(x, norm="backward"),
                        norm="backward"), atol=1e-6)
        assert_allclose(x, pypocketfft.irfft2(pypocketfft.rfft2(x, norm="ortho"),
                        norm="ortho"), atol=1e-6)
        assert_allclose(x, pypocketfft.irfft2(pypocketfft.rfft2(x, norm="forward"),
                        norm="forward"), atol=1e-6)

    def test_rfftn(self):
        x = random((30, 20, 10))
        assert_allclose(pypocketfft.fftn(x)[:, :, :6], pypocketfft.rfftn(x), atol=1e-6)
        assert_allclose(pypocketfft.rfftn(x),
                        pypocketfft.rfftn(x, norm="backward"), atol=1e-6)
        assert_allclose(pypocketfft.rfftn(x) / np.sqrt(30 * 20 * 10),
                        pypocketfft.rfftn(x, norm="ortho"), atol=1e-6)
        assert_allclose(pypocketfft.rfftn(x) / (30. * 20. * 10.),
                        pypocketfft.rfftn(x, norm="forward"), atol=1e-6)

    def test_irfftn(self):
        x = random((30, 20, 10))
        assert_allclose(x, pypocketfft.irfftn(pypocketfft.rfftn(x)), atol=1e-6)
        assert_allclose(x, pypocketfft.irfftn(pypocketfft.rfftn(x, norm="backward"),
                        norm="backward"), atol=1e-6)
        assert_allclose(x, pypocketfft.irfftn(pypocketfft.rfftn(x, norm="ortho"),
                        norm="ortho"), atol=1e-6)
        assert_allclose(x, pypocketfft.irfftn(pypocketfft.rfftn(x, norm="forward"),
                        norm="forward"), atol=1e-6)

    def test_hfft(self):
        x = random(14) + 1j*random(14)
        x_herm = np.concatenate((random(1), x, random(1)))
        x = np.concatenate((x_herm, x[::-1].conj()))
        assert_allclose(pypocketfft.fft(x), pypocketfft.hfft(x_herm), atol=1e-6)
        assert_allclose(pypocketfft.hfft(x_herm),
                        pypocketfft.hfft(x_herm, norm="backward"), atol=1e-6)
        assert_allclose(pypocketfft.hfft(x_herm) / np.sqrt(30),
                        pypocketfft.hfft(x_herm, norm="ortho"), atol=1e-6)
        assert_allclose(pypocketfft.hfft(x_herm) / 30.,
                        pypocketfft.hfft(x_herm, norm="forward"), atol=1e-6)

    def test_ihfft(self):
        x = random(14) + 1j*random(14)
        x_herm = np.concatenate((random(1), x, random(1)))
        x = np.concatenate((x_herm, x[::-1].conj()))
        assert_allclose(x_herm, pypocketfft.ihfft(pypocketfft.hfft(x_herm)), atol=1e-6)
        assert_allclose(x_herm, pypocketfft.ihfft(pypocketfft.hfft(x_herm,
                        norm="backward"), norm="backward"), atol=1e-6)
        assert_allclose(x_herm, pypocketfft.ihfft(pypocketfft.hfft(x_herm,
                        norm="ortho"), norm="ortho"), atol=1e-6)
        assert_allclose(x_herm, pypocketfft.ihfft(pypocketfft.hfft(x_herm,
                        norm="forward"), norm="forward"), atol=1e-6)

    @pytest.mark.parametrize("op", [pypocketfft.fftn, pypocketfft.ifftn,
                                    pypocketfft.rfftn, pypocketfft.irfftn])
    def test_axes(self, op):
        x = random((30, 20, 10))
        axes = [(0, 1, 2), (0, 2, 1), (1, 0, 2), (1, 2, 0), (2, 0, 1), (2, 1, 0)]
        for a in axes:
            op_tr = op(np.transpose(x, a))
            tr_op = np.transpose(op(x, axes=a), a)
            assert_allclose(op_tr, tr_op, atol=1e-6)

    def test_all_1d_norm_preserving(self):
        # verify that round-trip transforms are norm-preserving
        x = random(30)
        x_norm = np.linalg.norm(x)
        n = x.size * 2
        func_pairs = [(pypocketfft.fft, pypocketfft.ifft),
                      (pypocketfft.rfft, pypocketfft.irfft),
                      # hfft: order so the first function takes x.size samples
                      #       (necessary for comparison to x_norm above)
                      (pypocketfft.ihfft, pypocketfft.hfft),
                      ]
        for forw, back in func_pairs:
            for n in [x.size, 2*x.size]:
                for norm in [None, 'backward', 'ortho', 'forward']:
                    tmp = forw(x, n=n, norm=norm)
                    tmp = back(tmp, n=n, norm=norm)
                    assert_allclose(x_norm,
                                    np.linalg.norm(tmp), atol=1e-6)

    @pytest.mark.parametrize("dtype", [np.half, np.single, np.double,
                                       np.longdouble])
    def test_dtypes(self, dtype):
        # make sure that all input precisions are accepted and internally
        # converted to 64bit
        x = random(30).astype(dtype)
        assert_allclose(pypocketfft.ifft(pypocketfft.fft(x)), x, atol=1e-6)
        assert_allclose(pypocketfft.irfft(pypocketfft.rfft(x)), x, atol=1e-6)


@pytest.mark.parametrize(
        "dtype",
        [np.float32, np.float64, np.complex64, np.complex128])
@pytest.mark.parametrize("order", ["F", 'non-contiguous'])
@pytest.mark.parametrize(
        "fft",
        [pypocketfft.fft, pypocketfft.fft2, pypocketfft.fftn,
         pypocketfft.ifft, pypocketfft.ifft2, pypocketfft.ifftn])
def test_fft_with_order(dtype, order, fft):
    # Check that FFT/IFFT produces identical results for C, Fortran and
    # non contiguous arrays
    rng = np.random.RandomState(42)
    X = rng.rand(8, 7, 13).astype(dtype, copy=False)
    # See discussion in pull/14178
    _tol = 8.0 * np.sqrt(np.log2(X.size)) * np.finfo(X.dtype).eps
    if order == 'F':
        Y = np.asfortranarray(X)
    else:
        # Make a non contiguous array
        Y = X[::-1]
        X = np.ascontiguousarray(X[::-1])

    if fft.__name__.endswith('fft'):
        for axis in range(3):
            X_res = fft(X, axis=axis)
            Y_res = fft(Y, axis=axis)
            assert_allclose(X_res, Y_res, atol=_tol, rtol=_tol)
    elif fft.__name__.endswith(('fft2', 'fftn')):
        axes = [(0, 1), (1, 2), (0, 2)]
        if fft.__name__.endswith('fftn'):
            axes.extend([(0,), (1,), (2,), None])
        for ax in axes:
            X_res = fft(X, axes=ax)
            Y_res = fft(Y, axes=ax)
            assert_allclose(X_res, Y_res, atol=_tol, rtol=_tol)
    else:
        raise ValueError()


class TestFFTThreadSafe:
    threads = 16
    input_shape = (800, 200)

    def _test_mtsame(self, func, *args):
        def worker(args, q):
            q.put(func(*args))

        q = queue.Queue()
        expected = func(*args)

        # Spin off a bunch of threads to call the same function simultaneously
        t = [threading.Thread(target=worker, args=(args, q))
             for i in range(self.threads)]
        [x.start() for x in t]

        [x.join() for x in t]
        # Make sure all threads returned the correct value
        for i in range(self.threads):
            assert_array_equal(q.get(timeout=5), expected,
                'Function returned wrong value in multithreaded context')

    def test_fft(self):
        a = np.ones(self.input_shape) * 1+0j
        self._test_mtsame(pypocketfft.fft, a)

    def test_ifft(self):
        a = np.ones(self.input_shape) * 1+0j
        self._test_mtsame(pypocketfft.ifft, a)

    def test_rfft(self):
        a = np.ones(self.input_shape)
        self._test_mtsame(pypocketfft.rfft, a)

    def test_irfft(self):
        a = np.ones(self.input_shape) * 1+0j
        self._test_mtsame(pypocketfft.irfft, a)
