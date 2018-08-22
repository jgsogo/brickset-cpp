
#pragma once

#include <string>
#include <optional>

namespace brickset {

    class Set
    {
    public:
        virtual std::optional<std::reference_wrapper<const std::string>> number() const = 0;
        virtual std::optional<std::reference_wrapper<const std::string>> name() const = 0;
    };

}
