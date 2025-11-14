// xlsxzipwriter.cpp

#include "xlsxzipwriter_p.h"

#include <gen/files/ziputil.h>

#include <QDebug>
#include <QtGlobal>

QT_BEGIN_NAMESPACE_XLSX

ZipWriter::ZipWriter(const QString &filePath)
{
    m_zipFileName = filePath;
}

ZipWriter::~ZipWriter()
{
}

bool ZipWriter::error() const
{
    return false; // dummy for compatibility
}

void ZipWriter::addFile(const QString &filePath, const QByteArray &data)
{
    ZipUtil::getInstance().AddFile(m_zipFileName, filePath, data);
}

void ZipWriter::close()
{
    return; // dummy for compatibility
}

QT_END_NAMESPACE_XLSX
