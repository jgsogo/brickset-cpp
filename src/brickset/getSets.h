
#pragma once

#include "BricksetAPIv2Soap.nsmap"

#include "set.h"


namespace brickset {

    template <typename SetImplType>
    std::vector<std::unique_ptr<Set>> getSets(BricksetAPIv2SoapProxy& proxy,
        const std::string& api_key,
        const std::string& userHash,
        const std::string& query,
        const std::string& theme,
        const std::string& subtheme,
        const std::string& setNumber,
        int year,
        bool owned,
        bool wanted,
        const std::string& orderBy,
        int pageSize,
        int pageNumber,
        const std::string& userName
        )
    {
        static std::string true_bool_value = "1";
        static std::string empty_value = "";

        _ns1__getSets req;
        req.apiKey = (api_key != defaults::string) ? const_cast<std::string*>(&api_key) : &empty_value;
        req.query = (query != defaults::string) ? const_cast<std::string*>(&query) : &empty_value;
        req.userHash = (userHash != defaults::string) ? const_cast<std::string*>(&userHash) : &empty_value;
        req.theme = (theme != defaults::string) ? const_cast<std::string*>(&theme) : &empty_value;
        req.subtheme = (subtheme != defaults::string) ? const_cast<std::string*>(&subtheme) : &empty_value;
        req.setNumber = (setNumber != defaults::string) ? const_cast<std::string*>(&setNumber) : &empty_value;
        
        std::string yearStr = (year != defaults::integer) ? std::to_string(year) : empty_value;
        req.year = &yearStr;
        
        req.owned = owned ? &true_bool_value : &empty_value;
        req.wanted = wanted ? &true_bool_value : &empty_value;
        req.orderBy = (orderBy != defaults::string) ? const_cast<std::string*>(&orderBy) : &empty_value;
        
        std::string pageSizeStr = (pageSize != defaults::integer) ? std::to_string(pageSize) : empty_value;
        req.pageSize = &pageSizeStr;

        std::string pageNumberStr = (pageNumber != defaults::integer) ? std::to_string(pageNumber) : empty_value;
        req.pageNumber = &pageNumberStr;

        req.userName = (userName != defaults::string) ? const_cast<std::string*>(&userName) : &empty_value;

        _ns1__getSetsResponse response;
        auto r = proxy.getSets(&req, response);

        std::vector<std::unique_ptr<Set>> ret;
        if (response.getSetsResult)
        {
            for (auto& item : response.getSetsResult->sets)
            {
                ret.insert(ret.end(), std::make_unique<SetImplType>(item));
            }
        }
        return ret;
    }

}
