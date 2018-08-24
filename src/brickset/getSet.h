
#pragma once

//#include "BricksetAPIv2Soap.nsmap"

#include "set.h"


namespace brickset {

    template <typename SetImplType>
    std::unique_ptr<Set> getSet(BricksetAPIv2SoapProxy& proxy,
        const std::string& apiKey,
        const std::string& setId,
        const std::string& userHash
    )
    {
        static std::string empty_value = "";

        _ns1__getSet req;
        req.apiKey = (apiKey != defaults::string) ? const_cast<std::string*>(&apiKey) : &empty_value;
        req.SetID = (setId != defaults::string) ? const_cast<std::string*>(&setId) : &empty_value;
        req.userHash = (userHash != defaults::string) ? const_cast<std::string*>(&userHash) : &empty_value;

        _ns1__getSetResponse response;
        auto r = proxy.getSet(&req, response);

        if (response.getSetResult)
        {
            assert(response.getSetResult->sets.size() == 1);
            std::unique_ptr<Set> ret = std::make_unique<SetImplType>(response.getSetResult->sets.front());
            return ret;
        }
        return std::unique_ptr<Set>{};
    }

}
