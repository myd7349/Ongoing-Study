// 2015-02-04T15:52+08:00

#include "put_command.h"

#include <cassert>
#include <ctime>

#include <boost/filesystem.hpp>
#include <boost/progress.hpp>

#include "../../azure_cloud_storage_service.h"

void upload_block_blob(azure::storage::cloud_blob_container &container,
    const utility::string_t &local_file_path, const utility::string_t &target_blob_name,
    utility::size64_t uploading_bytes_each_time)
{
    if (!boost::filesystem::exists(local_file_path) || 
        !boost::filesystem::is_regular_file(local_file_path)) {
        ucerr << U('"') << local_file_path << U('"') << U(" doesn't exist or is not a regular file.\n");
        return;
    }

    auto blob = container.get_block_blob_reference(
        boost::filesystem::path(local_file_path).filename().native());

#if 1
    utility::size64_t file_size = boost::filesystem::file_size(local_file_path);
    if (0 == file_size) {
        blob.upload_from_file(local_file_path);
        return;
    }

    assert(uploading_bytes_each_time > 0);
    if (uploading_bytes_each_time == 0 || uploading_bytes_each_time > file_size) {
        uploading_bytes_each_time = file_size;
    }

    std::vector<std::uint8_t> buffer(uploading_bytes_each_time);

    utility::string_t block_id;
    std::uint64_t block_index = std::time(NULL);
    std::vector<azure::storage::block_list_item> block_list;

    // Since concurrency::streams::basic_istream doesn't provide us a "read" method looks like this:
    //   istream& read (char* s, streamsize n);
    // so, I use std::ifstream instead.
    std::ifstream in_file(local_file_path, std::ifstream::binary);
    if (!in_file) {
        ucout << U("Opening file \"") << local_file_path << U("\" failed.\n");
        return;
    }

    // Now, start the uploading process. If we want to upload a single block each time, then:
    //   C#:     PutBlock, PutBlockList
    //   Python: put_block, put_block_list
    //   Java:   uploadBlock, commitBlockList
    //   C++:    upload_block, upload_block_list
    ucout << U("Uploading file: ") << local_file_path << U("...");
    boost::progress_display prog(file_size);

    bool uploading = true;
    while (uploading) {
        // Generate an unique block id
        block_id = utility::conversions::to_base64(block_index++);
        // Read data
        in_file.read(reinterpret_cast<char *>(buffer.data()), uploading_bytes_each_time);
        if (!in_file) {
            auto bytes_read = in_file.gcount();
            if (bytes_read > 0) {
                buffer.resize(bytes_read);
                uploading = false;
            } else {
                break;
            }
        }
        // Upload the current block
        auto tmpStream = concurrency::streams::bytestream::open_istream(buffer);
        blob.upload_block(block_id, tmpStream, U(""));
        // Record the block id for following upload_block_list call
        block_list.push_back(azure::storage::block_list_item(block_id));
        // Upgrate the progress bar
        prog += in_file.gcount();
    }

    // The last step...
    blob.upload_block_list(block_list);
#elif 0
    blob.upload_from_file(local_file_path);
#elif 0
    auto in_stream = concurrency::streams::fstream::open_istream(local_file_path).get();
    blob.upload_from_stream(in_stream);
    in_stream.close().wait();
#endif
}

PutCommand::PutCommand()
{
    options_desc_.add_options()
        ("blob,b", boost::program_options::wvalue<utility::string_t>(&blob_name_)->required(), "The blob to download")
        ("in,i", boost::program_options::wvalue<utility::string_t>(&local_file_name_)->required(), "Local file name")
        //("step")
        ;
}

bool PutCommand::parse(const std::vector<utility::string_t> &vargs)
{
    container_name_.clear();
    blob_name_.clear();
    local_file_name_.clear();

    boost::program_options::variables_map args_map;

    try {
        boost::program_options::store(boost::program_options::basic_command_line_parser<CharT>(vargs).
            options(options_desc_).run(), args_map);
        boost::program_options::notify(args_map);

        return true;
    } catch (const std::exception &e) {
        notify_err(e.what(), PUT_COMMAND_STR);
        return false;
    }
}

bool PutCommand::run(AzureCloudStorageService *storage_service)
{
    if (container_name_.empty()) {
        if (!storage_service->current_container_.is_valid()) {
            ucerr << U("Container name didn't provided.\n");
        } else {
            upload_block_blob(storage_service->current_container_, local_file_name_, blob_name_, 1024 * 1024);
        }
    } else {
        auto container = storage_service->blob_client_.get_container_reference(container_name_);
        if (!container.exists()) {
            ucerr << U("Container \"") << container_name_ << U("\" doesn't exist.\n");
        } else {
            upload_block_blob(container, local_file_name_, blob_name_, 1024 * 1024);
        }
    }

    return true;
}

void PutCommand::help() const
{
    ucout << U("Download specified blob.\nUsage: ") << PUT_COMMAND_STR << U(" [options]\n");
    Command::help();
}
