// 2016-04-08T10:32+08:00
#ifndef FILTER_H_
#define FILTER_H_

class Filter {
public:
    Filter(int bufferLength);
    virtual ~Filter();

    Filter(const Filter &) = delete;
    Filter &operator=(const Filter &) = delete;

    double Run(double v);

private:
    int bufferLength_;
    double *buffer_;
    double *sortedBuffer_;
};

#endif // FILTER_H_