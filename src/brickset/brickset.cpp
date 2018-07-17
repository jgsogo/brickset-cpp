
#include "brickset.h"

#include "BricksetAPIv2Soap.nsmap"
#include "soapBricksetAPIv2SoapProxy.h"


namespace brickset {

    struct Brickset::Impl {
        Impl(const std::string& key) : api_key(key) {}
        const std::string api_key;
        BricksetAPIv2SoapProxy proxy;
    };

    Brickset::Brickset(const std::string& api_key) : _impl(std::make_unique<Impl>(api_key)) {}
    Brickset::~Brickset() {}

    void Brickset::whatever()
    {
        _ns1__checkKey request;
        request.apiKey = const_cast<std::string*>(&_impl->api_key);
        _ns1__checkKeyResponse response;

        std::cout << "Call 'checkKey'" << std::endl;
        auto r = _impl->proxy.checkKey(&request, response);
        std::cout << " - returned: " << r << std::endl;
        if (response.checkKeyResult)
        {
            std::cout << *response.checkKeyResult << std::endl;
        }
    }
}
