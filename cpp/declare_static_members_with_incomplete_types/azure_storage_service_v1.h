// 2015-03-09T11:16+08:00
#ifndef AZURE_STORAGE_SERVICE_V1_H_
#define AZURE_STORAGE_SERVICE_V1_H_

#include "was/blob.h"
#include "was/storage_account.h"

class AzureStorageServiceV1 {
    static azure::storage::cloud_storage_account storage_account_;
    static azure::storage::cloud_blob_client blob_client_;
};

#endif // AZURE_STORAGE_SERVICE_V1_H_
