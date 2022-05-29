#!/usr/bin/env python3
# coding: utf-8

import os.path
import urllib.request

import cppimport.import_hook  # noqa
import numpy as np
from numpy.core.multiarray import normalize_axis_index


_same_dir = lambda entry: os.path.join(os.path.dirname(__file__), entry)


def _download_pocketfft():
    sources = 'pocketfft.c', 'pocketfft.h'
    url = 'https://raw.githubusercontent.com/mreineck/pocketfft/master/'

    for source in sources:
        if not os.path.isfile(_same_dir(source)):
            urllib.request.urlretrieve(url + source, _same_dir(source))


def _import_pocketfft():
    _download_pocketfft()

    import pocketfft
    return pocketfft


_pocketfft = _import_pocketfft()


def _pairwise(iterable):
    "s -> (s0, s1), (s2, s3), (s4, s5), ..."
    a = iter(iterable)
    return zip(a, a)


def execute_real_forward(a, fct):
    a = np.asarray(a).copy()
    ndim = a.ndim
    odim = a.shape
    npts = odim[ndim-1]
    tdim = list(odim)
    tdim[ndim-1] = npts // 2 + 1
    cret = np.empty(tdim, dtype=np.complex128)
    tdim = [dim * 2 for dim in tdim]
    ret = np.empty(tdim, dtype=float)
    
    rstep = ret.shape[ret.ndim - 1]
    nrepeats = a.size // npts
    
    plan = _pocketfft.RFFT(npts)

    rptr = 0
    dptr = 0

    for i in range(nrepeats):
        ret[rptr+rstep-1] = 0
        ret[rptr+1:rptr+1+npts] = a[dptr:dptr+npts]

        if plan.forward(ret[rptr+1:], fct) != 0:
            raise RuntimeError('rfft_forward failed.')

        ret[rptr] = ret[rptr+1]
        ret[rptr+1] = 0
        
        rptr += rstep
        dptr += npts

    for index, (real, imag) in enumerate(_pairwise(ret)):
        cret[index] = real + imag * 1j

    return cret


def execute_real_backward(a, fct):
    a = np.asarray(a).astype(np.complex128).copy()
    npts = a.shape[a.ndim-1]
    ret = np.empty(a.shape, dtype=float)

    nrepeats = ret.size // npts
    
    plan = _pocketfft.RFFT(npts)

    rptr = 0
    dptr = 0

    a = a.view(float)

    for i in range(nrepeats):
        ret[rptr+1:rptr+1+npts-1] = a[dptr+2:dptr+2+npts-1]
        ret[rptr] = a[dptr]

        if plan.backward(ret[rptr:], fct) != 0:
            raise RuntimeError('rfft_backward failed.')

        rptr += npts
        dptr += npts * 2

    return ret


def execute_real(a, is_forward, fct):
    if is_forward:
        return execute_real_forward(a, fct)
    else:
        return execute_real_backward(a, fct)


def execute_complex(a, is_forward, fct):
    a = np.asarray(a).astype(np.complex128).copy()
    
    npts = a.shape[a.ndim-1]

    nrepeats = a.size // npts

    plan = _pocketfft.CFFT(npts)

    dptr = 0

    a = a.view(float)

    for i in range(nrepeats):
        if is_forward:
            res = plan.forward(a[dptr:], fct)
            if (res != 0):
                raise RuntimeError('cfft_forward failed.')
        else:
            res = plan.backward(a[dptr:1], fct)
            if (res != 0):
                raise RuntimeError('cfft_backward failed.')

        dptr += npts * 2

    return a.view(np.complex128)
    


def execute(a, is_real, is_forward, fct):
    if is_real:
        return execute_real(a, is_forward, fct)
    else:
        return execute_complex(a, is_forward, fct)


# `inv_norm` is a float by which the result of the transform needs to be
# divided. This replaces the original, more intuitive 'fct` parameter to avoid
# divisions by zero (or alternatively additional checks) in the case of
# zero-length axes during its computation.
def _raw_fft(a, n, axis, is_real, is_forward, inv_norm):
    axis = normalize_axis_index(axis, a.ndim)
    if n is None:
        n = a.shape[axis]

    fct = 1/inv_norm

    if a.shape[axis] != n:
        s = list(a.shape)
        index = [slice(None)]*len(s)
        if s[axis] > n:
            index[axis] = slice(0, n)
            a = a[tuple(index)]
        else:
            index[axis] = slice(0, s[axis])
            s[axis] = n
            z = np.zeros(s, a.dtype.char)
            z[tuple(index)] = a
            a = z

    if axis == a.ndim-1:
        r = execute(a, is_real, is_forward, fct)
    else:
        a = np.swapaxes(a, axis, -1)
        r = execute(a, is_real, is_forward, fct)
        r = np.swapaxes(r, axis, -1)
    return r


def _get_forward_norm(n, norm):
    if n < 1:
        raise ValueError(f"Invalid number of FFT data points ({n}) specified.")

    if norm is None or norm == "backward":
        return 1
    elif norm == "ortho":
        return np.sqrt(n)
    elif norm == "forward":
        return n
    raise ValueError(f'Invalid norm value {norm}; should be "backward",'
                     '"ortho" or "forward".')


def _get_backward_norm(n, norm):
    if n < 1:
        raise ValueError(f"Invalid number of FFT data points ({n}) specified.")

    if norm is None or norm == "backward":
        return n
    elif norm == "ortho":
        return np.sqrt(n)
    elif norm == "forward":
        return 1
    raise ValueError(f'Invalid norm value {norm}; should be "backward", '
                     '"ortho" or "forward".')


def fft(a, n=None, axis=-1, norm=None):
    a = np.asarray(a)
    if n is None:
        n = a.shape[axis]
    inv_norm = _get_forward_norm(n, norm)
    output = _raw_fft(a, n, axis, False, True, inv_norm)
    return output


def ifft(a, n=None, axis=-1, norm=None):
    a = np.asarray(a)
    if n is None:
        n = a.shape[axis]
    inv_norm = _get_backward_norm(n, norm)
    output = _raw_fft(a, n, axis, False, False, inv_norm)
    return output


def rfft(a, n=None, axis=-1, norm=None):
    a = np.asarray(a)
    if n is None:
        n = a.shape[axis]
    inv_norm = _get_forward_norm(n, norm)
    output = _raw_fft(a, n, axis, True, True, inv_norm)
    return output


def irfft(a, n=None, axis=-1, norm=None):
    a = np.asarray(a)
    if n is None:
        n = (a.shape[axis] - 1) * 2
    inv_norm = _get_backward_norm(n, norm)
    output = _raw_fft(a, n, axis, True, False, inv_norm)
    return output


def main():
    a = [1] * 8
    print(a)

    out = fft(a)
    print(out)
    print(np.fft.fft(a))

    out = rfft(a)
    print(out)
    print(np.fft.rfft(a))


if __name__ == '__main__':
    main()


# References:
# https://github.com/numpy/numpy/blob/main/numpy/fft/_pocketfft.c
# https://github.com/numpy/numpy/blob/main/numpy/fft/_pocketfft.py
# [How to ignore Pyflakes errors ‘imported but unused’ in the ‘__init__.py’ file?](https://stackoverflow.com/questions/8427701/how-to-ignore-pyflakes-errors-imported-but-unused-in-the-init-py-file)
# https://numpy.org/devdocs/reference/c-api/array.html
# https://numpy.org/doc/stable/reference/c-api/dtype.html
# https://numpy.org/doc/stable/user/basics.types.html
# [Convert complex NumPy array into (n, 2)-array of real and imaginary parts](https://stackoverflow.com/questions/38900344/convert-complex-numpy-array-into-n-2-array-of-real-and-imaginary-parts)
# [Iterating over every two elements in a list](https://stackoverflow.com/questions/5389507/iterating-over-every-two-elements-in-a-list)
# [Numpy: Creating a complex array from 2 real ones?](https://stackoverflow.com/questions/2598734/numpy-creating-a-complex-array-from-2-real-ones)
# [numpy's complex128 conversion](https://stackoverflow.com/questions/31794782/numpys-complex128-conversion)
# [How to convert a numpy complex array to a two element float array?](https://stackoverflow.com/questions/47086134/how-to-convert-a-numpy-complex-array-to-a-two-element-float-array)
