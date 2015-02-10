// 2015-01-29T16:44+08:00

#include "list_command.h"

#include <cassert>

#include <was/blob.h>
#include <was/storage_account.h>

#include "../../azure_cloud_storage_service.h"

bool ListCommand::parse(const std::vector<utility::string_t> &vargs)
{
    return parse_helper(vargs, LIST_COMMAND_STR);
}

bool ListCommand::run(AzureCloudStorageService *storage_service)
{
    if (container_name_.empty()) {
        if (!storage_service->current_container_.is_valid()) {
            ucout << U("Container list:\n");
            DumpLineByLine(get_container_list(storage_service->blob_client_));
        } else {
            ucout << U("Blobs under current container:\n");
            DumpLineByLine(get_blob_list(storage_service->current_container_));
        }
    } else {
        if (container_name_ == U("~")) {
            ucout << U("Container list:\n");
            DumpLineByLine(get_container_list(storage_service->blob_client_));
        } else {
            ucout << U("Blobs under container \"") << container_name_ << U("\":\n");
            DumpLineByLine(get_blob_list(storage_service->blob_client_, container_name_));
        }
    }

    return true;
}

void ListCommand::help() const
{
    ucout << U("Usage: ") << LIST_COMMAND_STR << U(" [container]\n");
    Command::help();
}

std::vector<utility::string_t> ListCommand::get_container_list(azure::storage::cloud_blob_client &blob_client)
{
    std::vector<utility::string_t> containers;
    
    azure::storage::continuation_token token;
    do {
        auto result_segment = blob_client.list_containers_segmented(token);
        for (const auto &c : result_segment.results()) {
            containers.push_back(c.name());
        }

        token = result_segment.continuation_token();
    } while (!token.empty());

    return containers;
}

std::vector<utility::string_t> ListCommand::get_blob_list(azure::storage::cloud_blob_client &blob_client,
    const utility::string_t &container_name)
{
    return get_blob_list(blob_client.get_container_reference(container_name));
}

std::vector<utility::string_t> ListCommand::get_blob_list(azure::storage::cloud_blob_container &blob_container)
{
    std::vector<utility::string_t> blobs;

    if (!blob_container.exists()) {
        ucerr << U("Container \"") << blob_container.name() << U("\" doesn't exist.\n");
        return blobs;
    }

    // https://github.com/Azure/azure-storage-cpp/blob/master/Microsoft.WindowsAzure.Storage/samples/BlobsGettingStarted/Application.cpp
    azure::storage::continuation_token token;
    do {
        // Here, I set "use_flat_blob_listing" as true so that I needn't to
        // walk the container recursively.
        //auto result = blob_container.list_blobs_segmented(token);
        auto result = blob_container.list_blobs_segmented(U(""), true,
            azure::storage::blob_listing_details::none, 0, token, 
            azure::storage::blob_request_options(), azure::storage::operation_context());

        for (const auto &b : result.blobs()) {
            blobs.push_back(b.uri().primary_uri().to_string());
        }

        token = result.continuation_token();
    } while (!token.empty());

    return blobs;
}
