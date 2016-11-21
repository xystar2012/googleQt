/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "errors"
 www.prokarpaty.net
***********************************************************/

#include "gmail/errors/ErrorsErrorInfo.h"
using namespace googleQt;

namespace googleQt{

namespace errors{
///ErrorInfo

ErrorInfo::operator QJsonObject()const{
    QJsonObject js;
    this->toJson(js);
    return js;
}


void ErrorInfo::toJson(QJsonObject& js)const{

    js["errors"] = struct_list2jsonarray(m_errors);
    js["code"] = m_code;
    if(!m_message.isEmpty())
        js["message"] = QString(m_message);
}

void ErrorInfo::fromJson(const QJsonObject& js){

    jsonarray2struct_list(js["errors"].toArray(), m_errors);
    m_code = js["code"].toVariant().toInt();
    m_message = js["message"].toString();
}

QString ErrorInfo::toString(bool multiline)const
{
    QJsonObject js;
    toJson(js);
    QJsonDocument doc(js);
    QString s(doc.toJson(multiline ? QJsonDocument::Indented : QJsonDocument::Compact));
    return s;
}


std::unique_ptr<ErrorInfo>  ErrorInfo::factory::create(const QByteArray& data)
{
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject js = doc.object();
    return create(js);
}


std::unique_ptr<ErrorInfo>  ErrorInfo::factory::create(const QJsonObject& js)
{
    std::unique_ptr<ErrorInfo> rv;
    rv = std::unique_ptr<ErrorInfo>(new ErrorInfo);
    rv->fromJson(js);
    return rv;
}

#ifdef API_QT_AUTOTEST
std::unique_ptr<ErrorInfo> ErrorInfo::EXAMPLE(){
    std::unique_ptr<ErrorInfo> rv(new ErrorInfo);
    rv->m_code = 2;
    rv->m_message = "test3value";
    return rv;
}
#endif //API_QT_AUTOTEST

}//errors
}//googleQt