#pragma once

// This is an imaginary new data format for an imaginary app.
/*
+-----------+
| meta info |
+-----------+
| real data |
+-----------+
*/
// The 'meta info' section is for storing meta information.
// And the 'real data' section is for storing real data.
// Once the file is created, the 'real data' can not be
// changed anymore. But the users can still edit the meta
// information stored in the file.
// As we can see, the 'real data' section is fixed-length
// once created. But the 'meta info' is a variable length
// section (It may contains variable length fields, or we
// may want to add more fields into it after).
// It is not a good idea to have a variable-length file header.
// But life is life, the meta information may change from
// time to time.
// However, we can change the data format a little:
/*
+------------------+
|   magic number   | (1) <- fixed length (6 bytes)
+------------------+
|   endian(L, B)   | (2) <- fixed length (1 byte), endian of (4), (5), (6)
+------------------|
|  has meta info   | (3) <- fixed length (1 byte), 'Y' means meta info is stored at the end of the file
+------------------+
| real data length | (4) <- fixed length (4 bytes unsigned integer)
+------------------+
|    real  data    | (5) <- fixed length once created
+------------------+
| meta info length | (6) <- fixed length (4 bytes unsigned integer)
+------------------+
|    meta  info    | (7) <- variable length
+------------------+
*/

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <google/protobuf/util/json_util.h>

#include "endian_utils.h"
#include "new_data_format_meta.pb.h"


namespace stdfs = std::experimental::filesystem;
namespace gpb = google::protobuf;
namespace ndf = newsoft::datamodel;

#define NDF_MAGIC "SUxTTA"
#define NDF_MAGIC_LENGTH 6
#define NDF_DATA_LENGTH_FIELD_LENGTH 4


inline void UpdateTimesatamp(gpb::Timestamp &timeStamp)
{
    timeStamp.set_seconds(std::time(nullptr));
    timeStamp.set_nanos(0);
}


auto PrintMetaInfo = [](const ndf::NDFMeta &meta)
{
    std::string json;

    gpb::util::JsonPrintOptions options;
    options.add_whitespace = true;
    options.always_print_primitive_fields = true;

    gpb::util::MessageToJsonString(meta, &json, options);

    std::cout << json << std::endl;
};


class NewDataFormat
{
public:
    NewDataFormat(int count, ndf::NDFMeta_DataWidth dataWidth, Endian endian)
        : endian_(endian)
        , metaInfoInSeperatedFile_(false)
    {
        if (count < 0)
            return;

        switch (dataWidth)
        {
#if 0
        case ndf::NDFMeta_DataWidth_DataWidthCustom:
            if (customDataWidth <= 0 || customDataWidth % 8 != 0)
                return nullptr;
            break;
#endif
        case ndf::NDFMeta_DataWidth_DataWidth8Bits: break;
        case ndf::NDFMeta_DataWidth_DataWidth16Bits: break;
#if 0
        case ndf::NDFMeta_DataWidth_DataWidth24Bits: break;
#endif
        case ndf::NDFMeta_DataWidth_DataWidth32Bits: break;
        default: return; break;
        }

        switch (endian)
        {
        case LittleEndian: break;
        case BigEndian: break;
        default: return; break;
        }

        data_.resize(count * static_cast<int>(dataWidth));

        meta_.set_data_width(dataWidth);
        UpdateTimesatamp(*meta_.mutable_created());
        UpdateTimesatamp(*meta_.mutable_last_edited());
    }

    NewDataFormat(const char *filePath, const char *metaFilePath = nullptr)
    {
        Load(filePath, metaFilePath);
    }

    bool Load(const char *filePath, const char *metaFilePath = nullptr)
    {
        if (filePath == nullptr || !stdfs::exists(filePath))
        {
            Clear();
            return false;
        }

        std::ifstream inStream(filePath, std::ios::binary);
        if (!inStream.is_open())
            return false;

        char magic[NDF_MAGIC_LENGTH];
        if (!inStream.read(magic, sizeof(magic)) || 
            std::strncmp(magic, NDF_MAGIC, NDF_MAGIC_LENGTH) != 0)
        {
            inStream.close();
            Clear();
            return false;
        }

        char endian;
        if (!inStream.read(&endian, 1) || (endian != 'L' && endian != 'B'))
        {
            inStream.close();
            Clear();
            return false;
        }

        endian_ = (endian == 'L' ? LittleEndian : BigEndian);

        char hasMetaInfo;
        if (!inStream.read(&hasMetaInfo, 1) || (hasMetaInfo != 'Y' && hasMetaInfo != 'N'))
        {
            inStream.close();
            Clear();
            return false;
        }

        metaInfoInSeperatedFile_ = hasMetaInfo == 'N';

        std::uint32_t dataLength;
        if (!inStream.read(reinterpret_cast<char *>(&dataLength), sizeof(dataLength)))
        {
            inStream.close();
            Clear();
            return false;
        }

        dataLength = ConvertEndian32(dataLength, endian_);
        data_.resize(dataLength);

        if (!inStream.read(reinterpret_cast<char *>(data_.data()), data_.size()))
        {
            inStream.close();
            Clear();
            return false;
        }

        bool ok = true;

        if (!metaInfoInSeperatedFile_)
        {
            std::uint32_t metaInfoLength;
            if (!inStream.read(reinterpret_cast<char *>(&metaInfoLength), sizeof(metaInfoLength)))
            {
                inStream.close();
                Clear();
                return false;
            }

            metaInfoLength = ConvertEndian32(metaInfoLength, endian_);
            std::vector<char> metaInfo(metaInfoLength);

            if (inStream.read(metaInfo.data(), metaInfo.size()))
                ok = meta_.ParseFromArray(metaInfo.data(), static_cast<int>(metaInfo.size()));
        }
        else
        {
            inStream.close();

            inStream.open(metaFilePath, std::ios::binary);
            if (inStream.is_open())
                ok = meta_.ParseFromIstream(&inStream);
        }

        inStream.close();

        if (ok)
        {
            switch (meta_.data_width())
            {
            case ndf::NDFMeta_DataWidth_DataWidth16Bits:
            {
                std::uint32_t count = dataLength / sizeof(std::uint16_t);
                std::uint16_t *data = reinterpret_cast<std::uint16_t *>(data_.data());
                for (std::uint32_t i = 0; i < count; ++i)
                    data[i] = ConvertEndian16(data[i], endian_);
            }
                break;
            case ndf::NDFMeta_DataWidth_DataWidth32Bits:
            {
                std::uint32_t count = dataLength / sizeof(std::uint32_t);
                std::uint32_t *data = reinterpret_cast<std::uint32_t *>(data_.data());
                for (std::uint32_t i = 0; i < count; ++i)
                    data[i] = ConvertEndian32(data[i], endian_);
            }
                break;
            }
        }
        else
        {
            Clear();
        }

        return ok;
    }

    Endian GetEndian() const
    {
        return endian_;
    }

    bool IsMetaInfoInSeperatedFile() const
    {
        return metaInfoInSeperatedFile_;
    }

    void SetMetaInfoInSeperatedFile(bool inSeperatedFile)
    {
        metaInfoInSeperatedFile_ = inSeperatedFile;
    }

    bool Save(const char *filePath, const char *metaFilePath = nullptr)
    {
        assert(filePath != nullptr);

        if (metaInfoInSeperatedFile_ && metaFilePath == nullptr)
            return false;

        std::ofstream outStream(filePath, std::ios::binary);
        if (!outStream.is_open())
            return false;

        outStream.write(NDF_MAGIC, NDF_MAGIC_LENGTH);
        outStream.write(endian_ == LittleEndian ? "L" : "B", 1);
        outStream.write(metaInfoInSeperatedFile_ ? "N" : "Y", 1);

        std::uint32_t dataLength = ConvertEndian32(static_cast<std::uint32_t>(data_.size()), endian_);
        outStream.write(reinterpret_cast<const char *>(&dataLength), sizeof(dataLength));

        if (endian_ == GetHostEndian())
        {
            outStream.write(reinterpret_cast<const char *>(data_.data()), data_.size());
        }
        else
        {
            switch (meta_.data_width())
            {
            case ndf::NDFMeta_DataWidth_DataWidth8Bits:
                outStream.write(reinterpret_cast<const char *>(data_.data()), data_.size());
                break;
            case ndf::NDFMeta_DataWidth_DataWidth16Bits:
            {
                std::size_t count = Count();
                std::vector<std::uint16_t> data(count);
                const std::uint16_t *dataBegin = reinterpret_cast<const std::uint16_t *>(data_.data());
                std::transform(dataBegin, dataBegin + count, data.begin(),
                    [this](std::uint16_t x) { return ConvertEndian16(x, endian_); });
                outStream.write(reinterpret_cast<const char *>(data.data()), count * sizeof(std::uint16_t));
            }
                break;
            case ndf::NDFMeta_DataWidth_DataWidth32Bits:
            {
                std::size_t count = Count();
                std::vector<std::uint32_t> data(count);
                const std::uint32_t *dataBegin = reinterpret_cast<const std::uint32_t *>(data_.data());
                std::transform(dataBegin, dataBegin + count, data.begin(),
                    [this](std::uint32_t x) { return ConvertEndian32(x, endian_); });
                outStream.write(reinterpret_cast<const char *>(data.data()), count * sizeof(std::uint32_t));
            }
                break;
            default: assert(false); break;
            }
        }

        if (!metaInfoInSeperatedFile_)
        {
            std::uint32_t metaInfoLength = ConvertEndian32(static_cast<std::uint32_t>(meta_.ByteSize()), endian_);
            outStream.write(reinterpret_cast<const char *>(&metaInfoLength), sizeof(metaInfoLength));

            bool ok = meta_.SerializeToOstream(&outStream);
            
            outStream.close();

            if (!ok)
                std::remove(filePath);

            return ok;
        }

        outStream.close();

        outStream.open(metaFilePath, std::ios::binary);
        if (!outStream.is_open())
        {
            std::remove(filePath);
            std::remove(metaFilePath);
            return false;
        }

        bool ok = meta_.SerializeToOstream(&outStream);

        if (!ok)
        {
            std::remove(filePath);
            std::remove(metaFilePath);
        }

        return ok;
    }

    void Clear()
    {
        endian_ = GetHostEndian();
        metaInfoInSeperatedFile_ = false;
        data_.clear();
        meta_.Clear();

        meta_.mutable_created()->Clear();
        meta_.mutable_last_edited()->Clear();
    }

    void Dump()
    {
        std::cout << "-------------------------------------------------------------------------------\n";

        std::cout << "Endian: " << GetEndianName(endian_) << '\n';
        std::cout << "Meta information stored in seperated file? " << metaInfoInSeperatedFile_ << '\n';
        std::cout << "Data length: " << data_.size() << '\n';
        std::cout << "Meta information length: " << meta_.ByteSize() << '\n';
        std::cout << "Meta information:\n";

        PrintMetaInfo(meta_);
    }

    std::string GetComment() const
    {
        return meta_.comment();
    }

    std::string SetComment(const char *comment)
    {
        auto oldComment = meta_.comment();
        meta_.mutable_comment()->assign(comment);
        UpdateTimesatamp(*meta_.mutable_last_edited());
        return oldComment;
    }

    std::size_t Count() const
    {
        switch (meta_.data_width())
        {
        case ndf::NDFMeta_DataWidth_DataWidth8Bits:
        case ndf::NDFMeta_DataWidth_DataWidth16Bits:
        case ndf::NDFMeta_DataWidth_DataWidth32Bits:
            return static_cast<size_t>(data_.size() / static_cast<int>(meta_.data_width()));
            break;
        default: return 0; break;
        }
    }

    std::uint32_t operator[](std::size_t i) const
    {
        if (i >= Count())
            throw std::out_of_range("Index out of range");

        switch (meta_.data_width())
        {
        case ndf::NDFMeta_DataWidth_DataWidth8Bits:
            return data_[i];
            break;
        case ndf::NDFMeta_DataWidth_DataWidth16Bits:
            return reinterpret_cast<const std::uint16_t *>(data_.data())[i];
            break;
        case ndf::NDFMeta_DataWidth_DataWidth32Bits:
            return reinterpret_cast<const std::uint32_t *>(data_.data())[i];
            break;
        default:
            throw std::runtime_error("Invalid data width");
            break;
        }
    }

#if 0
    /*
    NewDataFormat ndf(1024 * 1024 / 2, ndf::NDFMeta_DataWidth_DataWidth16Bits, BigEndian);
    ndf[0] = 10;
    */
    std::string operator[](std::string key) const
    {
        return GetProperty(key);
    }

    std::string &operator[](std::string key)
    {
        return meta_.mutable_properties()->operator[](key);
    }
#endif

    void SetData(std::size_t i, std::uint32_t value)
    {
        if (i >= Count())
            throw std::out_of_range("Index out of range");

        switch (meta_.data_width())
        {
        case ndf::NDFMeta_DataWidth_DataWidth8Bits:
            data_[i] = static_cast<std::uint8_t>(value);
            break;
        case ndf::NDFMeta_DataWidth_DataWidth16Bits:
            reinterpret_cast<std::uint16_t *>(data_.data())[i] = static_cast<std::uint16_t>(value);
            break;
        case ndf::NDFMeta_DataWidth_DataWidth32Bits:
            reinterpret_cast<std::uint32_t *>(data_.data())[i] = value;
            break;
        default:
            throw std::runtime_error("Invalid data width");
            break;
        }

        UpdateTimesatamp(*meta_.mutable_last_edited());
    }

    std::string GetProperty(std::string key, std::string defaultValue = "") const
    {
        auto properties = meta_.properties();
        auto it = properties.find(key);
        return it != properties.cend() ? it->second : defaultValue;
    }

    std::string SetProperty(std::string key, std::string value)
    {
        std::string oldProperty = GetProperty(key);
        (*meta_.mutable_properties())[key] = value;
        UpdateTimesatamp(*meta_.mutable_last_edited());
        return oldProperty;
    }

private:
    Endian endian_;
    bool metaInfoInSeperatedFile_;

    std::vector<std::uint8_t> data_;
    ndf::NDFMeta meta_;
};
