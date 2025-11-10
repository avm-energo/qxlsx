// xlsxzipreader_p.h

#pragma once
#include "xlsxglobal.h"

#include <QIODevice>
#include <QStringList>
#include <QVector>

QT_BEGIN_NAMESPACE_XLSX

class ZipReader
{
public:
    explicit ZipReader(const QString &fileName);
    ~ZipReader();
    bool exists() const;
    QStringList filePaths() const;
    QByteArray fileData(const QString &fileName) const;

private:
    Q_DISABLE_COPY(ZipReader)
    void init();
    QString m_filePath;
    QStringList m_filePaths;
};

QT_END_NAMESPACE_XLSX
