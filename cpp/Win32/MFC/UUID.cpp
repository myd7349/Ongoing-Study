#include "UUID.h"


CString GenerateUUID()
{
    UUID uuid = { 0 };
    UuidCreate(&uuid);

    CString strUuid;

    RPC_WSTR wszUuid = nullptr;
    if (UuidToStringW(&uuid, &wszUuid) == RPC_S_OK)
    {
        strUuid = (WCHAR *)wszUuid;
        RpcStringFreeW(&wszUuid);
    }

    return strUuid;
}


// References:
// [C++ UUID to stl string](https://stackoverflow.com/questions/24981119/c-uuid-to-stl-string)
