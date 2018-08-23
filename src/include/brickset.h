
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "set.h"

namespace brickset {

    namespace defaults {
        constexpr const char string[] = "";
        constexpr const int integer = 0;
    }

    class Brickset {
    public:
        Brickset(const std::string& api_key);
        ~Brickset();

        bool checkKey() const;
        std::optional<std::string> login(const std::string& username, const std::string& password) const;
        std::optional<std::string> checkUserHash(const std::string& userHash) const;

        // Sets
        template <bool deep_copy>
        std::vector<std::unique_ptr<Set>> getSets(
            const std::string& userHash = defaults::string,
            const std::string& query = defaults::string,
            const std::string& theme = defaults::string,
            const std::string& subtheme = defaults::string,
            const std::string& setNumber = defaults::string,
            int year = defaults::integer,
            bool owned = false,
            bool wanted = false,
            const std::string& orderBy = defaults::string,
            int pageSize = 20,
            int pageNumber = 1,
            const std::string& userName = defaults::string
        );

        template <bool deep_copy>
        std::unique_ptr<Set> getSet(
            const std::string& setId,
            const std::string& userHash = defaults::string
        ) const;

    protected:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

    // getSets
    template <> std::vector<std::unique_ptr<Set>> Brickset::getSets<true>(const std::string& userHash, const std::string& query, const std::string& theme, const std::string& subtheme, const std::string& setNumber, int year, bool owned, bool wanted, const std::string& orderBy, int pageSize, int pageNumber, const std::string& userName);
    template <> std::vector<std::unique_ptr<Set>> Brickset::getSets<false>(const std::string& userHash, const std::string& query, const std::string& theme, const std::string& subtheme, const std::string& setNumber, int year, bool owned, bool wanted, const std::string& orderBy, int pageSize, int pageNumber, const std::string& userName);

    // getSet
    template <> std::unique_ptr<Set> Brickset::getSet<true>(const std::string& setId, const std::string& userHash) const;
    template <> std::unique_ptr<Set> Brickset::getSet<false>(const std::string& setId, const std::string& userHash) const;
}

