
#include "include/brickset.h"

#include <functional>
//#include "BricksetAPIv2Soap.nsmap"
#include "soapBricksetAPIv2SoapProxy.h"

#include "getSets.h"
#include "getSet.h"


namespace brickset {

    namespace keywords {
        const std::string ok = "OK";
        const std::string invalid_key = "INVALIDKEY";
        const std::string invalid = "INVALID";
        const std::string error_prefix = "ERROR:";
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

    Brickset::Brickset(const std::string& api_key) : _impl(std::make_unique<Impl>(api_key))
    {

    }

    Brickset::~Brickset() {}

    bool Brickset::checkKey() const
    {
        _ns1__checkKey req;
        req.apiKey = const_cast<std::string*>(&_impl->api_key);

        _ns1__checkKeyResponse response;
        auto r = _impl->proxy.checkKey(&req, response);
        return (*response.checkKeyResult == keywords::ok);
    }

    std::optional<std::string> Brickset::login(const std::string& username, const std::string& password) const
    {
        _ns1__login req;
        req.apiKey = const_cast<std::string*>(&_impl->api_key);
        req.username = const_cast<std::string*>(&username);
        req.password = const_cast<std::string*>(&password);

        _ns1__loginResponse response;
        auto r = _impl->proxy.login(&req, response);
        if (*response.loginResult != keywords::invalid_key)
        {
            if (response.loginResult->compare(0, keywords::error_prefix.size(), keywords::error_prefix) != 0)
            {
                return std::optional<std::string>{*response.loginResult};
            }
        }
        return std::nullopt;
    }

    std::optional<std::string> Brickset::checkUserHash(const std::string& userHash) const
    {
        _ns1__checkUserHash req;
        req.userHash = const_cast<std::string*>(&userHash);

        _ns1__checkUserHashResponse response;
        auto r = _impl->proxy.checkUserHash(&req, response);
        return (*response.checkUserHashResult != keywords::invalid) ? std::optional<std::string>{*response.checkUserHashResult} : std::nullopt;
    }

    template <>
    std::vector<std::unique_ptr<Set>> Brickset::getSets<true>(
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
        int year,
        bool owned,
        bool wanted,
        const std::string& orderBy,
        int pageSize,
        int pageNumber,
        const std::string& userName
        )
    {
        return ::brickset::getSets<_detail::SetReference>(_impl->proxy, _impl->api_key, userHash, query, theme, subtheme, setNumber, year, owned,
            wanted, orderBy, pageSize, pageNumber, userName);
    }

    template <>
    std::unique_ptr<Set> Brickset::getSet<true>(const std::string& setId, const std::string& userHash) const
    {
        return ::brickset::getSet<_detail::SetDeepCopy>(_impl->proxy, _impl->api_key, setId, userHash);
    }

    template <>
    std::unique_ptr<Set> Brickset::getSet<false>(const std::string& setId, const std::string& userHash) const
    {
        return ::brickset::getSet<_detail::SetReference>(_impl->proxy, _impl->api_key, setId, userHash);
    }


}
