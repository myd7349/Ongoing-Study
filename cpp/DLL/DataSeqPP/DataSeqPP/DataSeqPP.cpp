#define DATASEQPP_API __declspec(dllexport)
#include "DataSeqPP.h"

#include <cassert>
#include <memory>
#include <stdexcept>

#include "../../DataSequenceV2/DataSeq/DataSeq.h"


class DataSequenceImpl {
public:
    explicit DataSequenceImpl(unsigned int size = 0)
    {
        handle_ = DataSeq_CreateV2(size);
    }

    virtual ~DataSequenceImpl()
    {
        if (handle_ != nullptr)
            DataSeq_Free(handle_);
    }

    void push_back(double v)
    {
        validate_and_throw_(DataSeq_PushBack(handle_, v));
    }

    double pop_back()
    {
        double v;
        validate_and_throw_(DataSeq_PopBack(handle_, &v));
        return v;
    }

    unsigned int size() const
    {
        return DataSeq_GetSizeV2(handle_);
    }

    double at(unsigned int i) const
    {
        double v;
        validate_and_throw_(DataSeq_GetAt(handle_, i, &v));
        return v;
    }

    double &at(unsigned int i)
    {
        if (i >= size())
            throw std::out_of_range("Index out of range");

        double *data_ = data();
        if (nullptr == data_)
            throw std::runtime_error("Memory error");

        return *(data_ + i);
    }

    const double *data() const
    {
        return DataSeq_GetDataV2(handle_);
    }

    double *data()
    {
        return DataSeq_GetDataV2(handle_);
    }

private:
    void validate_and_throw_(Error error) const
    {
        assert(handle_ != nullptr);
        assert(error == NoError);

        if (nullptr == handle_)
            throw std::runtime_error("Invalid DataSeq handle");

        switch (error) {
        case NoError: break;
        case IndexOutOfRange: throw std::out_of_range("Index out of range"); break;
        case InvalidParameter: throw std::invalid_argument("Invalid argument"); break;
        case InvalidOperation: throw std::runtime_error("Invalid operation"); break;
        case MemoryError: throw std::runtime_error("Memory error");  break;
        case UnknownError: throw std::runtime_error("Unknown error"); break;
        default: assert(false); break;
        }
    }

    DataSeqHandle handle_ = nullptr;
};


DataSequence::DataSequence(unsigned int size)
    : impl_(new DataSequenceImpl(size))
{
}

DataSequence::~DataSequence()
{
    if (impl_ != nullptr)
        delete impl_;
}

void DataSequence::push_back(double v)
{
    validate_and_throw_();
    impl_->push_back(v);
}

double DataSequence::pop_back()
{
    validate_and_throw_();
    return impl_->pop_back();
}

unsigned int DataSequence::size() const
{
    validate_and_throw_();
    return impl_->size();
}

double DataSequence::at(unsigned int i) const
{
    validate_and_throw_();
    return impl_->at(i);
}

double &DataSequence::at(unsigned int i)
{
    validate_and_throw_();
    return impl_->at(i);
}

double DataSequence::operator[](unsigned int i) const
{
    return at(i);
}

double &DataSequence::operator[](unsigned int i)
{
    return at(i);
}

const double *DataSequence::data() const
{
    validate_and_throw_();
    return impl_->data();
}

double *DataSequence::data()
{
    validate_and_throw_();
    return impl_->data();
}

void DataSequence::validate_and_throw_() const
{
    if (nullptr == impl_)
        throw std::runtime_error("Memory error");
}
