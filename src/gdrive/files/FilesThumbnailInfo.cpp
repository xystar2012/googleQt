/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "files"
 www.prokarpaty.net
***********************************************************/

#include "gdrive/files/FilesThumbnailInfo.h"
using namespace googleQt;

namespace googleQt{

namespace files{
///ThumbnailInfo

ThumbnailInfo::operator QJsonObject()const{
    QJsonObject js;
    this->toJson(js);
    return js;
}


void ThumbnailInfo::toJson(QJsonObject& js)const{

    js["image"] = m_image.constData();
    if(!m_mimeType.isEmpty())
        js["mimeType"] = QString(m_mimeType);
}

void ThumbnailInfo::fromJson(const QJsonObject& js){

    m_image = js["image"].toVariant().toByteArray();
    m_mimeType = js["mimeType"].toString();
}

QString ThumbnailInfo::toString(bool multiline)const
{
    QJsonObject js;
    toJson(js);
    QJsonDocument doc(js);
    QString s(doc.toJson(multiline ? QJsonDocument::Indented : QJsonDocument::Compact));
    return s;
}


std::unique_ptr<ThumbnailInfo>  ThumbnailInfo::factory::create(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject js = doc.object();
    return create(js);
}


std::unique_ptr<ThumbnailInfo>  ThumbnailInfo::factory::create(const QJsonObject& js)
{
    std::unique_ptr<ThumbnailInfo> rv;
    rv = std::unique_ptr<ThumbnailInfo>(new ThumbnailInfo);
    rv->fromJson(js);
    return rv;
}

#ifdef API_QT_AUTOTEST
std::unique_ptr<ThumbnailInfo> ThumbnailInfo::EXAMPLE(){
    std::unique_ptr<ThumbnailInfo> rv(new ThumbnailInfo);
    rv->m_image = QByteArray("AUTOTEST-DATA").toBase64();
    rv->m_mimeType = "test2value";
    return rv;
}
#endif //API_QT_AUTOTEST

}//files
}//googleQt