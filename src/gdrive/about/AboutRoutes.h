/**********************************************************
 DO NOT EDIT
 This file was generated from stone specification "about"
 www.prokarpaty.net
***********************************************************/

#pragma once

#include "google/endpoint/ApiUtil.h"
#include "gdrive/GdriveRequestArg.h"
#include "GoogleRouteBase.h"
#include "gdrive/about/AboutAboutResource.h"

namespace googleQt{
namespace about{


    class AboutRoutes: public GoogleRouteBase{
    public:
        AboutRoutes(Endpoint* ep):GoogleRouteBase(ep){};
            /**
            ApiRoute('get')


            Gets information about the user, the user's Drive, and system
            capabilities.

            */
        std::unique_ptr<AboutResource> get(const gdrive::AboutArg& arg);

    protected:
    };//AboutRoutes

}//about
}//googleQt