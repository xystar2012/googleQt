/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "labels"
 www.prokarpaty.net
***********************************************************/

#include "gmail/labels/LabelsLabelResource.h"
using namespace googleQt;

namespace googleQt{

namespace labels{
///LabelResource

LabelResource::operator QJsonObject()const{
    QJsonObject js;
    this->toJson(js);
    return js;
}


void LabelResource::toJson(QJsonObject& js)const{

    if(!m_id.isEmpty())
        js["id"] = QString(m_id);
    if(!m_name.isEmpty())
        js["name"] = QString(m_name);
    if(!m_messageListVisibility.isEmpty())
        js["messageListVisibility"] = QString(m_messageListVisibility);
    if(!m_labelListVisibility.isEmpty())
        js["labelListVisibility"] = QString(m_labelListVisibility);
    if(!m_type.isEmpty())
        js["type"] = QString(m_type);
    js["messagesTotal"] = m_messagesTotal;
    js["messagesUnread"] = m_messagesUnread;
    js["threadsTotal"] = m_threadsTotal;
}

void LabelResource::fromJson(const QJsonObject& js){

    m_id = js["id"].toString();
    m_name = js["name"].toString();
    m_messageListVisibility = js["messageListVisibility"].toString();
    m_labelListVisibility = js["labelListVisibility"].toString();
    m_type = js["type"].toString();
    m_messagesTotal = js["messagesTotal"].toVariant().toInt();
    m_messagesUnread = js["messagesUnread"].toVariant().toInt();
    m_threadsTotal = js["threadsTotal"].toVariant().toInt();
}

QString LabelResource::toString(bool multiline)const
{
    QJsonObject js;
    toJson(js);
    QJsonDocument doc(js);
    QString s(doc.toJson(multiline ? QJsonDocument::Indented : QJsonDocument::Compact));
    return s;
}


std::unique_ptr<LabelResource>  LabelResource::factory::create(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject js = doc.object();
    return create(js);
}


std::unique_ptr<LabelResource>  LabelResource::factory::create(const QJsonObject& js)
{
    std::unique_ptr<LabelResource> rv;
    rv = std::unique_ptr<LabelResource>(new LabelResource);
    rv->fromJson(js);
    return rv;
}

#ifdef API_QT_AUTOTEST
std::unique_ptr<LabelResource> LabelResource::EXAMPLE(){
    std::unique_ptr<LabelResource> rv(new LabelResource);
    rv->m_id = "test1value";
    rv->m_name = "test2value";
    rv->m_messageListVisibility = "test3value";
    rv->m_labelListVisibility = "test4value";
    rv->m_type = "test5value";
    rv->m_messagesTotal = 6;
    rv->m_messagesUnread = 7;
    rv->m_threadsTotal = 8;
    return rv;
}
#endif //API_QT_AUTOTEST

}//labels
}//googleQt