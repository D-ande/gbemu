#include <fstream>

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
                                    (std::istreambuf_iterator<char>())); //iterators are a singlepass interator

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

    std::cout << "Cartridge Loaded:" << std::endl;
    std::cout << "\tTitle    : " << m_romHeader->title << std::endl;
    std::cout << "\tType     : " << std::format("{:#x}", m_romHeader->cartType) << " (" << cartTypeName() << ")" << std::endl;
    std::cout << "\tROM Size : " << std::format("{:#x}", m_romHeader->romSize) << " (" << 32 * (1 << m_romHeader->romSize) << " KiB)" << std::endl;
    std::cout << "\tRAM Size : " << std::format("{:#x}", m_romHeader->ramSize) << " (" << cartRamSize() << " KiB)" << std::endl;
    std::cout << "\tLIC Code : " << std::format("{:#x}", m_romHeader->licCode) << " (" << cartLicName() << ")" << std::endl;
    std::cout << "\tROM Vers : " << std::format("{:d}", m_romHeader->romVersion) << std::endl;
    std::cout << "\tChecksum : " << std::format("{:#x}", m_romHeader->checksum) << " (" << (calcChecksum() ? "PASSED" : "FAILED") << ")" << std::endl;

    return calcChecksum();
}

std::string Cart::cartTypeName()
{
    std::string cartType{};
    try
    {
        cartType = CART_TYPE.at(m_romHeader->cartType);
    }
    catch (std::out_of_range)
    {
        cartType = "UNKNOWN";
    }
    
    return cartType;
}

std::string Cart::cartLicName()
{
    std::string licCode{};
    try
    {
        licCode = LIC_CODE.at(m_romHeader->licCode);
    }
    catch (std::out_of_range)
    {
        licCode = "UNKNOWN";
    }
    
    return licCode;
}

std::string Cart::cartRamSize()
{
    std::string ramSize{};
    try
    {
        ramSize = std::to_string(RAM_SIZE.at(m_romHeader->ramSize));
    }
    catch (std::out_of_range)
    {
        ramSize = "UNKNOWN";
    }
    
    return ramSize;
}

bool Cart::calcChecksum()
{
    uint8_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++)
    {
        checksum = checksum - m_romData[address] - 1;
    }
    
    if(checksum == m_romHeader->checksum){
        return true;
    }
    return false;
}

std::vector<uint8_t> Cart::getRomData()
{
    return m_romData;
}

uint8_t Cart::cartRead(uint16_t addr)
{
    return m_romData[addr];
}