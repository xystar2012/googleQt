#pragma once

#include "google/endpoint/ApiUtil.h"
#include "google/endpoint/ApiAutotest.h"

#ifdef API_QT_AUTOTEST
namespace googleQt{
    class GoogleClient;

    class GoogleAutotest: public ApiAutotest{
    public:
        GoogleAutotest(std::shared_ptr<GoogleClient> cl);
        virtual ~GoogleAutotest();
        void generateCalls()override;
        QString userId()const override;
        void setClient(std::shared_ptr<GoogleClient> cl);
    protected:
        std::shared_ptr<GoogleClient> m_cl;
    };
};//googleQt

#define DECLARE_AUTOTEST_INSTANCE(C, F) GoogleAutotest autotest(c);                     \
if (!autotest.init(F)) {                                                                \
    std::cout << "Error opening autotest output file " << F << std::endl;               \
    std::cin.ignore();                                                                  \
    return 0;                                                                           \
}                                                                                       \

#else
#define DECLARE_AUTOTEST_INSTANCE(C, F)
#endif//#ifdef API_QT_AUTOTEST
