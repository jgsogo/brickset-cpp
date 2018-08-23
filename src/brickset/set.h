
#pragma once

#include "include/set.h"

#include "soapBricksetAPIv2SoapProxy.h"

namespace brickset {
    namespace _detail {

        class SetReference : public Set
        {
        public:
            SetReference(ns1__sets* set);
            virtual ~SetReference();

            virtual std::optional<std::reference_wrapper<const std::string>> number() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> name() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> year() const final;

        protected:
            ns1__sets * _set;
        };

        class SetDeepCopy : public Set
        {
        public:
            SetDeepCopy(ns1__sets* set);

            virtual std::optional<std::reference_wrapper<const std::string>> number() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> name() const final;
            virtual std::optional<std::reference_wrapper<const std::string>> year() const final;

        protected:
            std::optional<std::string> _number, _name, _year;
        };

} }
