#ifndef Q7ZIP_H
#define Q7ZIP_H

#include <QObject>
#include <QLibrary>


class Q7Zip : public QObject
{
    Q_OBJECT

public:
    explicit Q7Zip(QObject *parent = 0);

    enum Operation
    {
        Q7ZIP_COMPRESS = 0U,
        Q7ZIP_EXTRACT,
        Q7ZIP_SHOWLIST
    };
    Q_ENUM(Operation)

    int compress(const QString &archive_name, const QStringList &compress_filelist, const QString &working_path);
    int extract(const QString &archive_name, const QString &output_path);
    int showfilelist(const QString &archive_name);

    static QString lzma_sdk_version();

signals:
    void operation_signal_compress(const QString archive_name, const QStringList compress_filelist, const QString working_path);
    void operation_signal_extract(const QString archive_name, const QString output_path);
    void operation_result_signal(Q7Zip::Operation operation, const QString archive_filename, int result);

    void compress_filesize_signal(const quint64 filesize);
    void compress_completeValue_signal(const quint64 completeValue);
    void compressing_filename_signal(const QString filename);

    void extract_filesize_signal(const quint64 filesize);
    void extract_completeValue_signal(const quint64 completeValue);
    void extract_percentage_signal(int percentage);
    void extracting_filename_signal(const QString filename);

public slots:
    void operation_slot_compress(const QString archive_name, const QStringList compress_filelist, const QString working_path);
    void operation_slot_extract(const QString archive_name, const QString output_path);

private:
    int init();

    QLibrary m_7zLib;
};

#endif // Q7ZIP_H


/*
————————————————
版权声明：本文为CSDN博主「AsukaV_V」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/AsukaV_V/article/details/83994492
*/
