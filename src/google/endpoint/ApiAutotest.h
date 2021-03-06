#pragma once
#include <stdio.h>
#include "google/endpoint/ApiUtil.h"
#include <QFile>
#include <QTextStream>
#include <QNetworkRequest>

namespace googleQt{

#ifdef API_QT_AUTOTEST
    using IDSET = std::set<QString>;
    using CLASS_ID_MAP = std::map<QString, IDSET>;
    using BATCH_LIST = std::list<std::pair<QString, googleQt::EBatchId>>;
    using CLASS2BATCH_LIST = std::map<QString, BATCH_LIST>;
#endif

    class ApiClient;

    class ApiAutotest{
    public:
        ApiAutotest();
        virtual ~ApiAutotest();

        bool init(QString filePathName);
        void close();
        virtual void generateCalls() = 0;
        virtual QString userId()const = 0;

        #ifdef API_QT_AUTOTEST
        static ApiAutotest& INSTANCE();
        ApiAutotest& operator << (const char * string);
        ApiAutotest& operator << (const QString & string);
        ApiAutotest& operator << (const QByteArray & array);
        ApiAutotest& operator << (const QNetworkRequest & req);
        ApiAutotest& operator << (const int & val);

        void prepareAutoTestObj(const char* context_class_name, const char* class_name, void* p, int idx, int context_index);
        QByteArray generateData(const char* context_class_name, int context_index, int parent_context_index);
        void logRequest(QString req);
        void enableRequestLog(bool val) { m_request_log_enabled = val; };
        void addId(const char* class_name, QString id);
        void addBatchId(const char* class_name, std::pair<QString, googleQt::EBatchId> bid);
        void addIdSet(const char* class_name, const IDSET& id_list);
        void addBatchIdList(const char* class_name, const BATCH_LIST& bid_list);
        QString getId(const char* class_name, int default_id_num);        
        IDSET getReservedIdSet(const char* class_name);
        BATCH_LIST getReservedBatchList(const char* class_name);
        quint64 getInt(const char* class_name, const char* field_name, int default_id_num);
        QString getString(const char* class_name, const char* field_name, QString default_value);

        bool isAttachmentDataGenerationEnabled()const{return m_attachmentDataGenerationOn;}
        void enableAttachmentDataGeneration(bool val){m_attachmentDataGenerationOn = val;}

        bool isProgressEmulationEnabled()const { return m_progress_emul_enabled; }
        void enableProgressEmulation(bool val) { m_progress_emul_enabled = val; }

        void emulateAutotestDownloadProgress(googleQt::ApiClient* cl);
        void sleep(int millisecondsToWait);

    protected:
        CLASS_ID_MAP m_availID;
        CLASS2BATCH_LIST m_availBatchID;
        bool m_attachmentDataGenerationOn{true};
        #endif //API_QT_AUTOTEST

    protected:
        FILE* m_out{nullptr};
        void log_string(const char*);

        bool  m_request_log_enabled{ true };
        bool  m_progress_emul_enabled{ true };
    };//ApiAutotest

}//googleQt
