
#include <iostream>
#include "../brickset/brickset.h"


int main() {
    std::cout << "**********************" << std::endl;

    brickset::Brickset ws("API_KEY");
    ws.whatever();
    //ws.getSets("star wars");
}
