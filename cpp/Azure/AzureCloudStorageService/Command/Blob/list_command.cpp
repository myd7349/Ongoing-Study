// 2015-01-29T16:44+08:00

#include "list_command.h"

#include <cassert>

#include <was/blob.h>
#include <was/storage_account.h>

#include "../../azure_cloud_storage_service.h"

ListCommand::ListCommand()
{
    options_desc_.add_options()
        ("container,c", boost::program_options::wvalue<utility::string_t>(&container_name_), "Specify the target container name")
        ;
}

bool ListCommand::parse(const std::vector<utility::string_t> &vargs)
{
    container_name_.clear();

    boost::program_options::positional_options_description container_name_option;
    container_name_option.add("container", 1);

    boost::program_options::variables_map args_map;

    try {
        using CharT = utility::string_t::traits_type::char_type;

        boost::program_options::store(boost::program_options::basic_command_line_parser<CharT>(vargs).
            options(options_desc_).positional(container_name_option).run(), args_map);
        boost::program_options::notify(args_map);

        return true;
    } catch (const std::exception &e) {
        notify_err(e.what(), LIST_COMMAND_STR);
        return false;
    }
}

bool ListCommand::run(AzureCloudStorageService *storage_service)
{
    utility::string_t target_container;

    if (container_name_.empty()) {
        if (storage_service->current_container_name_.empty()) {
            ucout << U("Container list:\n");
            DumpLineByLine(get_container_list(storage_service->blob_client_));
        } else {
            ucout << U("Blobs under current container:\n");
            DumpLineByLine(get_blob_list(storage_service->current_container_));
        }
    } else {
        ucout << U("Blobs under container \"") << container_name_ << U("\":\n");
        DumpLineByLine(get_blob_list(storage_service->blob_client_, container_name_));
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
        auto result = blob_container.list_blobs_segmented(token);
        for (const auto &b : result.blobs()) {
            blobs.push_back(b.uri().primary_uri().to_string());
        }

        token = result.continuation_token();
    } while (!token.empty());

    return blobs;
}
