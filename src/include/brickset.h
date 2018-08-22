
#pragma once

#include <memory>
#include <string>
#include <vector>

#include "set.h"

namespace brickset {

    class Brickset {
    public:
        Brickset(const std::string& api_key);
        ~Brickset();

        template <bool deep_copy>
        std::vector<std::unique_ptr<Set>> getSets(
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
        );
    protected:
        struct Impl;
        std::unique_ptr<Impl> _impl;
    };

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
        );

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
        );

}

