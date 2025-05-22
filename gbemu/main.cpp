#include <iostream>

#include "cart.hpp"

int main(int argc, char* argv[])
{
    std::string fileName{"/home/dalton/projects/gbemu/test_roms/01-special.gb"};

    if(argc > 2)
    {
        std::cerr << "Expected 1 input arument " << argc << " were given" << std::endl;
    }
    else if (argc < 2)
    {
        //Keep fileName same
    }
    else
    {
        std::string fileName = argv[1];
    }

    Cart* cart = new Cart();
    
    try
    {
        cart->loadCart(fileName);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 0;
    }
    
    return 1;
}