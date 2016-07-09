# -*- coding: utf-8 -*-

# 2016-07-09T17:28+08:00

import contextlib
from ctypes import (
    cast as _cast,
    windll as _windll,
    WINFUNCTYPE as _WINFUNCTYPE,
    pointer,
    sizeof,
    WinError,
    )
from ctypes.wintypes import (
    BOOL,
    BYTE,
    DWORD,
    LPCSTR,
    PBYTE,
    PDWORD,
    UINT,
    ULONG,
    )
import mmap


# MSDN & WinCrypt.h:
# typedef unsigned int ALG_ID;
# typedef ULONG_PTR HCRYPTPROV;
# typedef ULONG_PTR HCRYPTKEY;
# typedef ULONG_PTR HCRYPTHASH;
#
# #if defined(_WIN64)
#   typedef unsigned __int64 ULONG_PTR;
# #else
#   typedef unsigned long ULONG_PTR;
# #endif
HCRYPTPROV = ULONG
PHCRYPTPROV = PDWORD
HCRYPTKEY = ULONG
PHCRYPTKEY = PDWORD
HCRYPTHASH = ULONG
PHCRYPTHASH = PDWORD
ALG_ID = UINT

# BOOL WINAPI CryptAcquireContext(HCRYPTPROV*, LPCTSTR, LPCTSTR, DWORD, DWORD);
_CryptAcquireContextA_prototype = _WINFUNCTYPE(BOOL, PHCRYPTPROV, LPCSTR, LPCSTR, DWORD, DWORD)
# BOOL WINAPI CryptCreateHash(HCRYPTPROV, ALG_ID, HCRYPTKEY, DWORD, HCRYPTHASH*);
_CryptCreateHash_prototype = _WINFUNCTYPE(BOOL, HCRYPTPROV, ALG_ID, HCRYPTKEY, DWORD, PHCRYPTHASH)
# BOOL WINAPI CryptDuplicateHash(HCRYPTHASH, DWORD*, DWORD, HCRYPTHASH*);
#_CryptDuplicateHash_prototype = _WINFUNCTYPE(BOOL, HCRYPTHASH, PDWORD, DWORD, PHCRYPTHASH)
# BOOL WINAPI CryptHashData(HCRYPTHASH, BYTE*, DWORD, DWORD);
_CryptHashData_prototype = _WINFUNCTYPE(BOOL, HCRYPTHASH, PBYTE, DWORD, DWORD)
# BOOL WINAPI CryptGetHashParam(HCRYPTHASH, DWORD, BYTE*, DWORD*, DWORD);
_CryptGetHashParam_prototype = _WINFUNCTYPE(BOOL, HCRYPTHASH, DWORD, PBYTE, PDWORD, DWORD)
# BOOL WINAPI CryptDestroyHash(HCRYPTHASH);
_CryptDestroyHash_prototype = _WINFUNCTYPE(BOOL, HCRYPTHASH)
# BOOL WINAPI CryptReleaseContext(HCRYPTPROV, DWORD);
_CryptReleaseContext_prototype = _WINFUNCTYPE(BOOL, HCRYPTPROV, DWORD)

_advapi32 = _windll.advapi32
CryptAcquireContextA = _CryptAcquireContextA_prototype(('CryptAcquireContextA', _advapi32))
CryptCreateHash = _CryptCreateHash_prototype(('CryptCreateHash', _advapi32))
#CryptDuplicateHash = _CryptDuplicateHash_prototype(('CryptDuplicateHash', _advapi32))
CryptHashData = _CryptHashData_prototype(('CryptHashData', _advapi32))
CryptGetHashParam = _CryptGetHashParam_prototype(('CryptGetHashParam', _advapi32))
CryptDestroyHash = _CryptDestroyHash_prototype(('CryptDestroyHash', _advapi32))
CryptReleaseContext = _CryptReleaseContext_prototype(('CryptReleaseContext', _advapi32))

PROV_RSA_FULL = DWORD(1)

_ALG_CLASS_HASH = 4 << 13
_ALG_TYPE_ANY = 0
_ALG_SID_MD5 = 3
_ALG_SID_SHA1 = 4

CALG_MD5 = ALG_ID(_ALG_CLASS_HASH | _ALG_TYPE_ANY | _ALG_SID_MD5)
CALG_SHA1 = ALG_ID(_ALG_CLASS_HASH | _ALG_TYPE_ANY | _ALG_SID_SHA1)

HP_HASHVAL = DWORD(0x0002)
HP_HASHSIZE = DWORD(0x0004)

MD5 = 0
SHA1 = 1
SHA_256 = 2
SHA_384 = 3
SHA_512 = 4

_calg_map = {
    MD5: CALG_MD5,
    SHA1: CALG_SHA1,
    }


@contextlib.contextmanager
def _crypt_context():
    hCryptProv = HCRYPTPROV()
    res = CryptAcquireContextA(pointer(hCryptProv), None, None, PROV_RSA_FULL, DWORD(0))
    if not res:
        raise WinError()
    
    try:
        yield hCryptProv
    finally:
        CryptReleaseContext(hCryptProv, DWORD(0))


@contextlib.contextmanager
def _crypt_hash(hCryptProv, calg):
    hCryptHash = HCRYPTHASH()
    res = CryptCreateHash(hCryptProv, calg, HCRYPTKEY(0), DWORD(0), pointer(hCryptHash))
    if not res:
        raise WinError()

    try:
        yield hCryptHash
    finally:
        CryptDestroyHash(hCryptHash)


class InvalidHashAlgorithm(Exception): pass


def hash_file(file, alg, block_size=16*1024):
    with open(file, 'r+b') as fp:
        with mmap.mmap(fp.fileno(), 0) as mm:
            return hash_data(mm, alg, block_size)


def hash_data(buffer, alg, block_size=16*1024):
    if alg not in _calg_map:
        raise InvalidHashAlgorithm()
    
    block_size = int(block_size)
    if block_size <= 0:
        raise ValueError("'block_size' should be a positive integer")

    with _crypt_context() as hCryptProv:
        with _crypt_hash(hCryptProv, _calg_map[alg]) as hCryptHash:
            buffer_len = len(buffer)
            if block_size > buffer_len:
                block_size = buffer_len

            i = 0
            while i < buffer_len:
                count = block_size if (i + block_size <= buffer_len) else (buffer_len - i)
                if not CryptHashData(hCryptHash, _cast(buffer[i:i+count], PBYTE), DWORD(count), DWORD(0)):
                    raise WinError()
                i += count

            dwHashLen = DWORD(sizeof(DWORD))
            dwHashSize = DWORD()
            if not CryptGetHashParam(hCryptHash, HP_HASHSIZE, _cast(pointer(dwHashSize), PBYTE), pointer(dwHashLen), DWORD(0)):
                raise WinError()

            pbHashVal = (BYTE * dwHashSize.value)()
            dwHashLen.value = sizeof(pbHashVal)
            if not CryptGetHashParam(hCryptHash, HP_HASHVAL, pbHashVal, pointer(dwHashLen), DWORD(0)):
                raise WinError()

            return ''.join(map(lambda b: format(b, '02x'), bytes(pbHashVal)))


def main():
    pass


if __name__ == '__main__':
    main()
