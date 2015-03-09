// 2015-03-09T11:19+08:00
#ifndef AZURE_STORAGE_SERVICE_V2_H_
#define AZURE_STORAGE_SERVICE_V2_H_

namespace azure { namespace storage {
        class cloud_storage_account;
        class cloud_blob_client;
}
}

class AzureStorageServiceV2 {
    static azure::storage::cloud_storage_account storage_account_;
    static azure::storage::cloud_blob_client blob_client_;
};

#endif // AZURE_STORAGE_SERVICE_V2_H_
