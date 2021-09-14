#pragma once

#include <QObject>


class Q7Zip;


class ExtractionWorker : public QObject
{
    Q_OBJECT

public:
    ExtractionWorker();
    ~ExtractionWorker();

public slots:
    void extract();

signals:
    void extraction_percentage_updated(int percentage);

private:
    Q7Zip *q7zip_;
};
