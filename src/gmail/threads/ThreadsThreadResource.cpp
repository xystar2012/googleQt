/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "threads"
 www.prokarpaty.net
***********************************************************/

#include "gmail/threads/ThreadsThreadResource.h"
using namespace googleQt;

namespace googleQt{

namespace threads{
///ThreadResource

ThreadResource::operator QJsonObject()const{
    QJsonObject js;
    this->toJson(js);
    return js;
}


void ThreadResource::toJson(QJsonObject& js)const{

    if(!m_id.isEmpty())
        js["id"] = QString(m_id);
    if(!m_snipped.isEmpty())
        js["snipped"] = QString(m_snipped);
    js["historyId"] = m_historyId;
    js["messages"] = struct_list2jsonarray(m_messages);
}

void ThreadResource::fromJson(const QJsonObject& js){

    m_id = js["id"].toString();
    m_snipped = js["snipped"].toString();
    m_historyId = js["historyId"].toVariant().toInt();
    jsonarray2struct_list(js["messages"].toArray(), m_messages);
}

QString ThreadResource::toString(bool multiline)const
{
    QJsonObject js;
    toJson(js);
    QJsonDocument doc(js);
    QString s(doc.toJson(multiline ? QJsonDocument::Indented : QJsonDocument::Compact));
    return s;
}


std::unique_ptr<ThreadResource>  ThreadResource::factory::create(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject js = doc.object();
    return create(js);
}


std::unique_ptr<ThreadResource>  ThreadResource::factory::create(const QJsonObject& js)
{
    std::unique_ptr<ThreadResource> rv;
    rv = std::unique_ptr<ThreadResource>(new ThreadResource);
    rv->fromJson(js);
    return rv;
}

#ifdef API_QT_AUTOTEST
std::unique_ptr<ThreadResource> ThreadResource::EXAMPLE(){
    std::unique_ptr<ThreadResource> rv(new ThreadResource);
    rv->m_id = "test1value";
    rv->m_snipped = "test2value";
    rv->m_historyId = 3;
    return rv;
}
#endif //API_QT_AUTOTEST

}//threads
}//googleQt