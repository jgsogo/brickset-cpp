
#pragma once

#include "BricksetAPIv2Soap.nsmap"
#include "soapBricksetAPIv2SoapProxy.h"

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
        const std::string& year,
        const std::string& owned,
        const std::string& wanted,
        const std::string& orderBy,
        const std::string& pageSize,
        const std::string& pageNumber,
        const std::string& userName)
    {
        _ns1__getSets req;
        req.apiKey = const_cast<std::string*>(&api_key);
        req.query = const_cast<std::string*>(&query);
        req.userHash = const_cast<std::string*>(&userHash);
        req.theme = const_cast<std::string*>(&theme);
        req.subtheme = const_cast<std::string*>(&subtheme);
        req.setNumber = const_cast<std::string*>(&setNumber);
        req.year = const_cast<std::string*>(&year);
        req.owned = const_cast<std::string*>(&owned);
        req.wanted = const_cast<std::string*>(&wanted);
        req.orderBy = const_cast<std::string*>(&orderBy);
        req.pageSize = const_cast<std::string*>(&pageSize);
        req.pageNumber = const_cast<std::string*>(&pageNumber);
        req.userName = const_cast<std::string*>(&userName);


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
