
#include "brickset.h"

#include "BricksetAPIv2Soap.nsmap"
#include "soapBricksetAPIv2SoapProxy.h"


namespace brickset {

    struct Set::Impl
    {
        ns1__sets* set;
    };

    class SetImpl : public Set
    {
        public:
            SetImpl(ns1__sets* set)
            {
                _impl->set = set;
            }
    };

    Set::Set() : _impl(std::make_unique<Impl>()) {}
    Set::~Set() {}

    const std::string& Set::number() const
    {
        return *_impl->set->number;
    }

    const std::string& Set::name() const
    {
        return *_impl->set->name;
    }


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

    std::vector<std::unique_ptr<Set>> Brickset::getSets(
                           const std::string& userHash, const std::string& query,
                           const std::string& theme, const std::string& subtheme, const std::string& setNumber,
                           const std::string& year, const std::string& owned, const std::string& wanted,
                           const std::string& orderBy, const std::string& pageSize, const std::string& pageNumber,
                           const std::string& userName)
    {
        _ns1__getSets req;
        req.apiKey = const_cast<std::string*>(&_impl->api_key);
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

        std::cout << "Call 'getSets(query='" << query << "')'" << std::endl;
        auto r = _impl->proxy.getSets(&req, response);
        std::cout << " - returned: " << r << std::endl;

        std::vector<std::unique_ptr<Set>> ret;
        if (response.getSetsResult)
        {
            for (auto& item : response.getSetsResult->sets)
            {
                ret.insert(ret.end(), std::make_unique<SetImpl>(item));
                //std::cout << *item->number << ": " << *item->name << std::endl;
            }
        }
        return ret;
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
