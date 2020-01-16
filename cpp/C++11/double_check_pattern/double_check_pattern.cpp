#include <algorithm>
#include <cstdint>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

const int RESOURCE_COUNT = 10;

struct GlobalResources {
  enum Flags : uint32_t { OCCUPIED = 0x80000000 };

  std::uint32_t handles_[RESOURCE_COUNT]{};
  std::mutex mutex_;
};

std::uint32_t *GetResource(GlobalResources &resources) {
  for (int i = 0; i < RESOURCE_COUNT; ++i) {
    if ((resources.handles_[i] & GlobalResources::OCCUPIED) == 0) {
      std::unique_lock<std::mutex> lock(resources.mutex_);

      if ((resources.handles_[i] & GlobalResources::OCCUPIED) != 0) {
        std::cout << "#" << std::this_thread::get_id() << ": Resource " << i
                  << " is used.\n";
        lock.unlock();
        continue;
      } else {
        std::cout << "#" << std::this_thread::get_id() << ": Get resource " << i
                  << std::endl;
        resources.handles_[i] |= GlobalResources::OCCUPIED;
        return &resources.handles_[i];
      }
    }
  }

  return nullptr;
}

void Callback(GlobalResources &resources) {
  while (true) {
    auto handle = GetResource(resources);
    if (handle != nullptr) {
      *handle |= 0x1;
      break;
    }
  }
}

int main() {
  GlobalResources resources;

  std::vector<std::thread> threads(RESOURCE_COUNT);
  for (int i = 0; i < RESOURCE_COUNT; ++i)
    threads[i] = std::thread(Callback, std::ref(resources));

  std::for_each(threads.begin(), threads.end(),
                [](std::thread &t) { t.join(); });

  for (int i = 0; i < RESOURCE_COUNT; ++i)
    std::cout << std::hex << resources.handles_[i] << std::endl;

  return 0;
}

// References:
// https://github.com/swig/swig/issues/1383
// C:\Program Files (x86)\Microsoft Visual Studio 10.0\VC\crt\src\osfinfo.c
#if 0
int __cdecl _alloc_osfhnd(
    void
)
{
    int fh = -1;    /* file handle */
    int i;
    ioinfo *pio;
    int failed = FALSE;

    if (!_mtinitlocknum(_OSFHND_LOCK))
        return -1;

    _mlock(_OSFHND_LOCK);   /* lock the __pioinfo[] array */
    __TRY

        /*
         * Search the arrays of ioinfo structs, in order, looking for the
         * first free entry. The compound index of this free entry is the
         * return value. Here, the compound index of the ioinfo struct
         * *(__pioinfo[i] + j) is k = i * IOINFO_ARRAY_ELTS + j, and k = 0,
         * 1, 2,... is the order of the search.
         */
        for (i = 0; i < IOINFO_ARRAYS; i++) {
            /*
             * If __pioinfo[i] is non-empty array, search it looking for
             * the first free entry. Otherwise, allocate a new array and use
             * its first entry.
             */
            if (__pioinfo[i] != NULL) {
                /*
                 * Search for an available entry.
                 */
                for (pio = __pioinfo[i];
                    pio < __pioinfo[i] + IOINFO_ARRAY_ELTS;
                    pio++)
                {
                    if ((pio->osfile & FOPEN) == 0) {
                        /*
                         * Make sure the lock is initialized.
                         */
                        if (pio->lockinitflag == 0) {
                            _mlock(_LOCKTAB_LOCK);
                            __TRY
                                if (pio->lockinitflag == 0) {
                                    if (!InitializeCriticalSectionAndSpinCount(&(pio->lock), _CRT_SPINCOUNT))
                                    {
                                        /*
                                         * Lock initialization failed.  Release
                                         * held locks and return failure.
                                        */
                                        failed = TRUE;
                                    }
                                    else
                                    {
                                        pio->lockinitflag++;
                                    }
                                }
                            __FINALLY
                                _munlock(_LOCKTAB_LOCK);
                            __END_TRY_FINALLY
                        }

                        if (!failed)
                        {
                            EnterCriticalSection(&(pio->lock));

                            /*
                            * Check for the case where another thread has
                            * managed to grab the handle out from under us.
                            */
                            if ((pio->osfile & FOPEN) != 0) {
                                LeaveCriticalSection(&(pio->lock));
                                continue;
                            }
                        }

                        if (!failed)
                        {
                            pio->osfile = FOPEN;
                            pio->osfhnd = (intptr_t)INVALID_HANDLE_VALUE;
                            fh = i * IOINFO_ARRAY_ELTS + (int)(pio - __pioinfo[i]);
                            break;
                        }
                    }
                }

                /*
                 * Check if a free entry has been found.
                 */
                if (fh != -1)
                    break;
            }
            else {
                /*
                 * Allocate and initialize another array of ioinfo structs.
                 */
                if ((pio = _calloc_crt(IOINFO_ARRAY_ELTS, sizeof(ioinfo)))
                    != NULL)
                {

                    /*
                     * Update __pioinfo[] and _nhandle
                     */
                    __pioinfo[i] = pio;
                    _nhandle += IOINFO_ARRAY_ELTS;

                    for (; pio < __pioinfo[i] + IOINFO_ARRAY_ELTS; pio++) {
                        pio->osfile = 0;
                        pio->osfhnd = (intptr_t)INVALID_HANDLE_VALUE;
                        pio->pipech = 10;
                        pio->lockinitflag = 0;
                    }

                    /*
                     * The first element of the newly allocated array of ioinfo
                     * structs, *(__pioinfo[i]), is our first free entry.
                     */
                    fh = i * IOINFO_ARRAY_ELTS;
                    _osfile(fh) = FOPEN;
                    if (!__lock_fhandle(fh)) {
                        /*
                         * The lock initialization failed, return the failure
                         */
                        fh = -1;
                    }
                }

                break;
            }
        }
    __FINALLY
        _munlock(_OSFHND_LOCK); /* unlock the __pioinfo[] table */
    __END_TRY_FINALLY

        /*
         * return the index of the previously free table entry, if one was
         * found. return -1 otherwise.
         */
        return(fh);
}
#endif
