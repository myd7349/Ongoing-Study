// 2016-04-05T16:19+08:00
#ifndef DATASEQPP_H_
#define DATASEQPP_H_

#ifndef DATASEQPP_API
# ifndef SWIG
#  define DATASEQPP_API __declspec(dllimport)
# else
#  define DATASEQPP_API
# endif
#endif


class DataSequenceImpl;

class DATASEQPP_API DataSequence {
public:
    explicit DataSequence(unsigned int size = 0);
    virtual ~DataSequence();

    DataSequence(const DataSequence &) = delete;
    DataSequence &operator=(const DataSequence &) = delete;

    void push_back(double v);
    double pop_back();
    unsigned int size() const;
    double at(unsigned int i) const;
    double &at(unsigned int i);
    double operator[](unsigned int i) const;
    double &operator[](unsigned int i);
    const double *data() const;
    double *data();

private:
    void validate_and_throw_() const;

    DataSequenceImpl *impl_;
};

#endif // DATASEQPP_H_
