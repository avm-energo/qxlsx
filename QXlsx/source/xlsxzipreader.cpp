// xlsxzipreader.cpp

#include "xlsxzipreader_p.h"

#include <gen/files/ziputil.h>

QT_BEGIN_NAMESPACE_XLSX

ZipReader::ZipReader(const QString &filePath)
{
    m_filePath = filePath;
    init();
}

ZipReader::~ZipReader()
{
}

void ZipReader::init()
{
    m_filePaths = ZipUtil::getInstance().GetArchiveContentsList(m_filePath);
}

bool ZipReader::exists() const
{
    return true; // dummy for compatibility
}

QStringList ZipReader::filePaths() const
{
    return m_filePaths;
}

QByteArray ZipReader::fileData(const QString &fileName) const
{
    return ZipUtil::getInstance().DecompressFileToBA(m_filePath, fileName);
}

QT_END_NAMESPACE_XLSX
