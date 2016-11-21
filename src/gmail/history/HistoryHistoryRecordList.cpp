/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "history"
 www.prokarpaty.net
***********************************************************/

#include "gmail/history/HistoryHistoryRecordList.h"
using namespace googleQt;

namespace googleQt{

namespace history{
///HistoryRecordList

HistoryRecordList::operator QJsonObject()const{
    QJsonObject js;
    this->toJson(js);
    return js;
}


void HistoryRecordList::toJson(QJsonObject& js)const{

    js["history"] = struct_list2jsonarray(m_history);
    if(!m_nextPageToken.isEmpty())
        js["nextPageToken"] = QString(m_nextPageToken);
    if(!m_historyId.isEmpty())
        js["historyId"] = QString(m_historyId);
}

void HistoryRecordList::fromJson(const QJsonObject& js){

    jsonarray2struct_list(js["history"].toArray(), m_history);
    m_nextPageToken = js["nextPageToken"].toString();
    m_historyId = js["historyId"].toString();
}

QString HistoryRecordList::toString(bool multiline)const
{
    QJsonObject js;
    toJson(js);
    QJsonDocument doc(js);
    QString s(doc.toJson(multiline ? QJsonDocument::Indented : QJsonDocument::Compact));
    return s;
}


std::unique_ptr<HistoryRecordList>  HistoryRecordList::factory::create(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject js = doc.object();
    return create(js);
}


std::unique_ptr<HistoryRecordList>  HistoryRecordList::factory::create(const QJsonObject& js)
{
    std::unique_ptr<HistoryRecordList> rv;
    rv = std::unique_ptr<HistoryRecordList>(new HistoryRecordList);
    rv->fromJson(js);
    return rv;
}

#ifdef API_QT_AUTOTEST
std::unique_ptr<HistoryRecordList> HistoryRecordList::EXAMPLE(){
    std::unique_ptr<HistoryRecordList> rv(new HistoryRecordList);
    rv->m_nextPageToken = "test2value";
    rv->m_historyId = "test3value";
    return rv;
}
#endif //API_QT_AUTOTEST

}//history
}//googleQt