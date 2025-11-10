// xlsxzipwriter_p.h

#pragma once
#include "xlsxglobal.h"

#include <QString>
#include <QtGlobal>

QT_BEGIN_NAMESPACE_XLSX

class ZipWriter
{
public:
    explicit ZipWriter(const QString &filePath);
    ~ZipWriter();

    void addFile(const QString &filePath, const QByteArray &data);
    bool error() const;
    void close();

private:
    QString m_zipFileName;
};

QT_END_NAMESPACE_XLSX
