/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "about"
 www.prokarpaty.net
***********************************************************/

#pragma once
#include "google/endpoint/ApiUtil.h"
#include "gdrive/GdriveRequestArg.h"
#include "gdrive/about/AboutUserInfo.h"

namespace googleQt{
namespace about{
    class AboutResource{
        /**
            field: kind: This is always drive#about.
            field: user: The authenticated user.
        */

    public:
        AboutResource():
        m_kind("drive#about")
        {};

        AboutResource(const QString& arg):
        m_kind("drive#about")
        { m_kind = arg; };

    public:
            /**
                This is always drive#about.
            */
        QString kind()const{return m_kind;};
        AboutResource& setKind(const QString& arg){m_kind=arg;return *this;};

            /**
                The authenticated user.
            */
        const UserInfo& user()const{return m_user;};
        AboutResource& setUser(const UserInfo& arg){m_user=arg;return *this;};

    public:
        operator QJsonObject ()const;
        virtual void fromJson(const QJsonObject& js);
        virtual void toJson(QJsonObject& js)const;
        virtual QString toString(bool multiline = true)const;


        class factory{
        public:
            static std::unique_ptr<AboutResource>  create(const QByteArray& data);
            static std::unique_ptr<AboutResource>  create(const QJsonObject& js);
        };


        #ifdef API_QT_AUTOTEST
        static std::unique_ptr<AboutResource> EXAMPLE();
        #endif //API_QT_AUTOTEST


    protected:
            /**
                This is always drive#about.
            */
        QString m_kind;

            /**
                The authenticated user.
            */
        UserInfo m_user;

    };//AboutResource

}//about
}//googleQt