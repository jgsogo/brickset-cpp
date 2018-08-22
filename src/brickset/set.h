
#pragma once

#include "include/set.h"

namespace brickset {
    namespace _detail {

        class SetReference : public Set
        {
        public:
            SetReference(ns1__sets* set) : _set(set) {}
            virtual ~SetReference() {}

            virtual std::optional<std::reference_wrapper<const std::string>> number() const final
            {
                return _set->number ? std::optional<std::reference_wrapper<const std::string>>{*_set->number} : std::nullopt;
            }

            virtual std::optional<std::reference_wrapper<const std::string>> name() const final
            {
                return _set->name ? std::optional<std::reference_wrapper<const std::string>>{*_set->name} : std::nullopt;
            }

        protected:
            ns1__sets * _set;
        };

        class SetDeepCopy : public Set
        {
        public:
            SetDeepCopy(ns1__sets* set)
            {
                if (set->number) _number = *set->number;
                if (set->name) _name = *set->name;
            }

            virtual std::optional<std::reference_wrapper<const std::string>> number() const final
            {
                return _number.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_number.value()} : std::nullopt;
            }

            virtual std::optional<std::reference_wrapper<const std::string>> name() const final
            {
                return _name.has_value() ? std::optional<std::reference_wrapper<const std::string>>{_name.value()} : std::nullopt;
            }

        protected:
            std::optional<std::string> _number, _name;
        };

} }
