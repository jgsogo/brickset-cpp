
#include "include/brickset.h"

#include <functional>
//#include "BricksetAPIv2Soap.nsmap"
#include "soapBricksetAPIv2SoapProxy.h"

#include "getSets.h"


namespace brickset {

    struct Brickset::Impl {
        Impl(const std::string& key) : api_key(key), proxy("https://brickset.com/api/v2.asmx")
        {
            proxy.soap->proxy_host = "localhost";
            proxy.soap->proxy_port = 3128;
            // SSL issues. https://stackoverflow.com/a/27907007/837816
            soap_ssl_client_context(proxy.soap, SOAP_SSL_NO_AUTHENTICATION, NULL, NULL, NULL, NULL, NULL);
            //proxy.soap->ssl_flags = SOAP_SSL_DEFAULT;
            //soap_register_plugin(proxy.soap, soap_wsse); // https://www.genivia.com/doc/wsse/html/wsse.html
            //proxy.soap->cafile = "cacerts.pem";
        }
        ~Impl()
        {
            proxy.destroy();
        }
        const std::string api_key;
        BricksetAPIv2SoapProxy proxy;
    };

    Brickset::Brickset(const std::string& api_key) : _impl(std::make_unique<Impl>(api_key))
    {

    }

    Brickset::~Brickset() {}

    template <>
    std::vector<std::unique_ptr<Set>> Brickset::getSets<true>(
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
        const std::string& userName
        )
    {
        return ::brickset::getSets<_detail::SetDeepCopy>(_impl->proxy, _impl->api_key, userHash, query, theme, subtheme, setNumber, year, owned,
            wanted, orderBy, pageSize, pageNumber, userName);
    }

    template <>
    std::vector<std::unique_ptr<Set>> Brickset::getSets<false>(
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
        const std::string& userName
        )
    {
        return ::brickset::getSets<_detail::SetReference>(_impl->proxy, _impl->api_key, userHash, query, theme, subtheme, setNumber, year, owned,
            wanted, orderBy, pageSize, pageNumber, userName);
    }

    /*
    void Brickset::whatever()
    {
        _ns1__checkKey request;
        request.apiKey = const_cast<std::string*>(&_impl->api_key);
        _ns1__checkKeyResponse response;

        std::cout << _impl->proxy.soap->endpoint << std::endl;

        std::cout << "Call 'checkKey'" << std::endl;
        auto r = _impl->proxy.checkKey(&request, response);
        if (r != SOAP_OK)
        {
            std::cout << "------ error " << r << " ------" << std::endl;
            soap_stream_fault(_impl->proxy.soap, std::cout);
            std::cout << "----------------------" << std::endl;
            std::cout << soap_strdup(_impl->proxy.soap, _impl->proxy.soap->endpoint) << std::endl;
        }
        else
        {
            if (response.checkKeyResult)
            {
                std::cout << *response.checkKeyResult << std::endl;
            }
        }
    }
    */
}
