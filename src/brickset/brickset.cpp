
#include "brickset.h"

#include "BricksetAPIv2Soap.nsmap"
#include "soapBricksetAPIv2SoapProxy.h"


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

    Brickset::Brickset(const std::string& api_key) : _impl(std::make_unique<Impl>(api_key)) {}
    Brickset::~Brickset() {}

    void Brickset::getSets(const std::string& query)
    {
        _ns1__getSets req;
        req.query = const_cast<std::string*>(&query);
        _ns1__getSetsResponse response;

        std::cout << "Call 'getSets'" << std::endl;
        auto r = _impl->proxy.getSets(&req, response);
        std::cout << " - returned: " << r << std::endl;
        if (response.getSetsResult)
        {
            for (auto& item : response.getSetsResult->sets)
            {
                std::cout << item << std::endl;
            }
        }
    }

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
}
