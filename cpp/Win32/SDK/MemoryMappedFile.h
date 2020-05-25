#ifndef MEMORY_MAPPED_FILE_H_
#define MEMORY_MAPPED_FILE_H_

#include <cassert>

#ifndef UNICODE
#define UNICODE
#endif

#ifndef _UNICODE
#define _UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


namespace MemoryMappedFiles
{
    class MemoryMappedFile
    {
    public:
        explicit MemoryMappedFile(LPCTSTR fileName)
            : MemoryMappedFile(CreateFile(
                fileName,
                GENERIC_READ | GENERIC_WRITE,
                FILE_SHARE_READ,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            ), false)
        {
        }

        explicit MemoryMappedFile(HANDLE file, bool leaveOpen = true)
            : file_(file), fileMapping_(NULL), mapName_(NULL), leaveOpen_(leaveOpen)
        {
        }

        LPCTSTR GetName() const
        {
            return mapName_;
        }

    private:
        void *Map(LPCTSTR mapName, DWORD sizeHigh, DWORD sizeLow)
        {
            if (file_ == INVALID_HANDLE_VALUE)
                return NULL;

            if (fileMapping_ == NULL)
                fileMapping_ = CreateFileMapping(
                    file_,
                    NULL,
                    PAGE_READWRITE,
                    0,
                    0,
                    mapName
                );

            if (fileMapping_ == NULL)
                return NULL;

            mapName_ = mapName;

            return MapViewOfFile(
                fileMapping_,
                FILE_MAP_ALL_ACCESS,
                sizeHigh,
                sizeLow,
                0);
        }

        HANDLE file_;
        HANDLE fileMapping_;
        LPCTSTR mapName_;
        bool leaveOpen_;
    };
}

#endif // MEMORY_MAPPED_FILE_H_
