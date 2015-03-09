// 2015-03-09T11:06+08:00
// When I was implementing an Azure storage service wrapper class for my project,
// I wrote a class named AzureStorageService.
//
// The version 1.0 of this class is shown in azure_storage_service_v1.h/cpp.
//
// However, I don't want to include so many header files in azure_storage_service_v1.h.
// Now, the question is, can I use a incomplete type when declaring these two static members:
//    static azure::storage::cloud_storage_account storage_account_;
//    static azure::storage::cloud_blob_client blob_client_;
// in the header file?//
// The answer:
// http://stackoverflow.com/a/3536498
//
#include "azure_storage_service_v1.h"
#include "azure_storage_service_v2.h"

int main()
{
    AzureStorageServiceV1 ass1;
    AzureStorageServiceV2 ass2;

    (void)ass1;
    (void)ass2;

    return 0;
}

// References:
// http://stackoverflow.com/questions/936446/is-it-possible-to-forward-declare-a-static-array
// [Defining static members in C++](http://stackoverflow.com/questions/3536372/defining-static-members-in-c)
