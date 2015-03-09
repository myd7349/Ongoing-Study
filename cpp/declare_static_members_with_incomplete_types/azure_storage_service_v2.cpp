// 2015-03-09T11:20+08:00
#include "azure_storage_service_v2.h"

#include "was/blob.h"
#include "was/storage_account.h"

azure::storage::cloud_storage_account AzureStorageServiceV2::storage_account_;
azure::storage::cloud_blob_client AzureStorageServiceV2::blob_client_;
