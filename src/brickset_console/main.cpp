
#include <iostream>
#include "include/brickset.h"


int main() {
    static std::string empty_value = "empty";

    std::cout << "**********************" << std::endl;
    const std::string env_brickset_api_key = "BRICKSET_API_KEY";
    std::vector<std::unique_ptr<brickset::Set>> sets;
    if (const char* brickset_key = std::getenv(env_brickset_api_key.c_str()))
    {
        brickset::Brickset ws{ brickset_key };
        if (!ws.checkKey())
        {
            std::cerr << "Invalid key provided to the library" << std::endl;
            return 1;
        }

        /*
        auto userHash = ws.login("username", "password");
        std::cout << "UserHash: " << userHash.value() << std::endl;

        auto userName = ws.checkUserHash(userHash.value());
        std::cout << "Username: " << userName.value() << std::endl;
        */

        //ws.whatever();
        sets = ws.getSets<true>(brickset::defaults::string, "8868", brickset::defaults::string,
            brickset::defaults::string, brickset::defaults::string, 1992);

        for (auto& set : sets)
        {
            std::cout << set->name().value_or(empty_value).get() << std::endl;
            std::cout << set->year().value_or(empty_value).get() << std::endl;
        }
    }
    else
    {
        std::cerr << "Provide an api key using environment variable " << env_brickset_api_key << std::endl;
        return 1;
    }

    // Ok. Los objectos de gSOAP parece que se destruyen cuando sale de scope el webservice.
    for (auto& set : sets)
    {
        std::cout << set->name().value_or(empty_value).get() << std::endl;
        std::cout << set->year().value_or(empty_value).get() << std::endl;
    }

}
