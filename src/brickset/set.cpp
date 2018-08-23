
#include "set.h"

namespace brickset {
    namespace _detail {

        SetReference::SetReference(ns1__sets* set) : _set(set) {}
        SetReference::~SetReference() {}

        std::optional<std::reference_wrapper<const std::string>> SetReference::number() const
        {
            return _set->number ? std::optional<std::reference_wrapper<const std::string>>{*_set->number} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetReference::name() const
        {
            return _set->name ? std::optional<std::reference_wrapper<const std::string>>{*_set->name} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetReference::year() const
        {
            return _set->year ? std::optional<std::reference_wrapper<const std::string>>{*_set->year} : std::nullopt;
        }

        SetDeepCopy::SetDeepCopy(ns1__sets* set)
        {
            if (set->number) _number = *set->number;
            if (set->name) _name = *set->name;
            if (set->year) _year = *set->year;
        }

        std::optional<std::reference_wrapper<const std::string>> SetDeepCopy::number() const
        {
            return _number.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_number.value()} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetDeepCopy::name() const
        {
            return _name.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_name.value()} : std::nullopt;
        }

        std::optional<std::reference_wrapper<const std::string>> SetDeepCopy::year() const
        {
            return _year.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_year.value()} : std::nullopt;
        }

    }
}


