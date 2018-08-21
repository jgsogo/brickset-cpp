
#pragma once

#include <memory>
#include <string>
#include <vector>

namespace brickset {

    class Set
    {
        public:
            Set();
            Set(const Set&) = delete;
            ~Set();
            const std::string& number() const;
            const std::string& name() const;

        protected:
            struct Impl;
            std::unique_ptr<Impl> _impl;
    };

    class Brickset {
        public:
            Brickset(const std::string& api_key);
            ~Brickset();

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

            void whatever();
        protected:
            struct Impl;
            std::unique_ptr<Impl> _impl;
    };

}

