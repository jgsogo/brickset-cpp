
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
        //ws.whatever();
        sets = ws.getSets<false>("8868", "", "", "", "", "", "", "", "", "", "", "");

        for (auto& set : sets)
        {
            std::cout << set->name().value_or(empty_value).get() << std::endl;
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
    }

    //ws.getSets("star wars");
}
