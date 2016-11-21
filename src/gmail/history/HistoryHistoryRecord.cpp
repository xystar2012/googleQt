/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "history"
 www.prokarpaty.net
***********************************************************/

#include "gmail/history/HistoryHistoryRecord.h"
using namespace googleQt;

namespace googleQt{

namespace history{
///HistoryRecord

HistoryRecord::operator QJsonObject()const{
    QJsonObject js;
    this->toJson(js);
    return js;
}


void HistoryRecord::toJson(QJsonObject& js)const{

    if(!m_id.isEmpty())
        js["id"] = QString(m_id);
    js["messages"] = struct_list2jsonarray(m_messages);
    js["messagesAdded"] = struct_list2jsonarray(m_messagesAdded);
    js["messagesDeleted"] = struct_list2jsonarray(m_messagesDeleted);
    js["labelsAdded"] = struct_list2jsonarray(m_labelsAdded);
    js["labelsRemoved"] = struct_list2jsonarray(m_labelsRemoved);
}

void HistoryRecord::fromJson(const QJsonObject& js){

    m_id = js["id"].toString();
    jsonarray2struct_list(js["messages"].toArray(), m_messages);
    jsonarray2struct_list(js["messagesAdded"].toArray(), m_messagesAdded);
    jsonarray2struct_list(js["messagesDeleted"].toArray(), m_messagesDeleted);
    jsonarray2struct_list(js["labelsAdded"].toArray(), m_labelsAdded);
    jsonarray2struct_list(js["labelsRemoved"].toArray(), m_labelsRemoved);
}

QString HistoryRecord::toString(bool multiline)const
{
    QJsonObject js;
    toJson(js);
    QJsonDocument doc(js);
    QString s(doc.toJson(multiline ? QJsonDocument::Indented : QJsonDocument::Compact));
    return s;
}


std::unique_ptr<HistoryRecord>  HistoryRecord::factory::create(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject js = doc.object();
    return create(js);
}


std::unique_ptr<HistoryRecord>  HistoryRecord::factory::create(const QJsonObject& js)
{
    std::unique_ptr<HistoryRecord> rv;
    rv = std::unique_ptr<HistoryRecord>(new HistoryRecord);
    rv->fromJson(js);
    return rv;
}

#ifdef API_QT_AUTOTEST
std::unique_ptr<HistoryRecord> HistoryRecord::EXAMPLE(){
    std::unique_ptr<HistoryRecord> rv(new HistoryRecord);
    rv->m_id = "test1value";
    return rv;
}
#endif //API_QT_AUTOTEST

}//history
}//googleQt