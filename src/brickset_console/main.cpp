
#include <iostream>
#include "../brickset/brickset.h"


int main() {
    std::cout << "**********************" << std::endl;
    const std::string env_brickset_api_key = "BRICKSET_API_KEY";
    if (const char* brickset_key = std::getenv(env_brickset_api_key.c_str()))
    {
        brickset::Brickset ws(brickset_key);
        ws.whatever();
        ws.getSets("8868");
    }
    else
    {
        std::cerr << "Provide an api key using environment variable " << env_brickset_api_key << std::endl;
        return 1;
    }
    //ws.getSets("star wars");
}
