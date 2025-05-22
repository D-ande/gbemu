#include <iostream>
#include <fstream>
#include <cstring>

#include "cart.hpp"

Cart::Cart()
{

}

Cart::~Cart()
{

}

bool Cart::loadCart(std::string romName)
{
    std::cout << "Loading: " << romName << std::endl;
    
    m_filename = romName;

    std::ifstream inputFile(m_filename);

    if (inputFile.is_open())
    {
        m_romData.assign((std::istreambuf_iterator<char>(inputFile)), 
                                    (std::istreambuf_iterator<char>())); //interators are a singlepass interator

        inputFile.close();
    }
    else
    {
        std::cerr << "Error opening file" << std::endl;
        return false;
    }

    m_romSize = m_romData.size();

    std::cout << "Rom Size: " << m_romSize << std::endl;

    uint8_t* romData = (uint8_t*)malloc(m_romSize);

    memcpy(romData, m_romData.data(), m_romSize);

    if(m_romSize - 0x100 > sizeof(m_romHeader))
    {      
        m_romHeader = (cartHeader*)(romData + 0x100);
    }
    else{
        std::cerr << "Error parsing romHeader, romData is smaller than header size" << std::endl;
    }

    printf("Cartridge Loaded:\n");
    printf("\tTitle : %s\n", m_romHeader->title);
    printf("\tType  : %2.2x (%s)\n", m_romHeader->cartType, cartTypeName().c_str());

    return true;
}

std::string Cart::cartTypeName()
{
    if(m_romHeader->cartType < 0xFF)
    {
        return CART_TYPE.at(m_romHeader->cartType);
    }
    return "UNKNOWN";
}

std::string Cart::cartLicName()
{
    if(m_romHeader->licCode <= 0xA4)
    {
        return LIC_CODE.at(m_romHeader->licCode);
    }
    return "UNKNOWN";
}