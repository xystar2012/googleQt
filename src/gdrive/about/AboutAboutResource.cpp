/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "about"
 www.prokarpaty.net
***********************************************************/

#include "gdrive/about/AboutAboutResource.h"
using namespace googleQt;

namespace googleQt{

namespace about{
///AboutResource

AboutResource::operator QJsonObject()const{
    QJsonObject js;
    this->toJson(js);
    return js;
}


void AboutResource::toJson(QJsonObject& js)const{

    if(!m_kind.isEmpty())
        js["kind"] = QString(m_kind);
    js["user"] = (QJsonObject)m_user;
}

void AboutResource::fromJson(const QJsonObject& js){

    m_kind = js["kind"].toString();
    m_user.fromJson(js["user"].toObject());
}

QString AboutResource::toString(bool multiline)const
{
    QJsonObject js;
    toJson(js);
    QJsonDocument doc(js);
    QString s(doc.toJson(multiline ? QJsonDocument::Indented : QJsonDocument::Compact));
    return s;
}


std::unique_ptr<AboutResource>  AboutResource::factory::create(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject js = doc.object();
    return create(js);
}


std::unique_ptr<AboutResource>  AboutResource::factory::create(const QJsonObject& js)
{
    std::unique_ptr<AboutResource> rv;
    rv = std::unique_ptr<AboutResource>(new AboutResource);
    rv->fromJson(js);
    return rv;
}

#ifdef API_QT_AUTOTEST
std::unique_ptr<AboutResource> AboutResource::EXAMPLE(){
    std::unique_ptr<AboutResource> rv(new AboutResource);
    rv->m_kind = "test1value";
    rv->m_user = *(about::UserInfo::EXAMPLE().get());
    return rv;
}
#endif //API_QT_AUTOTEST

}//about
}//googleQt