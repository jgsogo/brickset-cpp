
#pragma once

#include <memory>
#include <string>

namespace brickset {

    class Brickset {
        public:
            Brickset(const std::string& api_key);
            ~Brickset();

            void whatever();
        protected:
            struct Impl;
            std::unique_ptr<Impl> _impl;
    };

}

