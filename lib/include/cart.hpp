#pragma once

#include <cstdint>
#include <map>
#include <vector>

static const std::map<uint8_t, std::string> CART_TYPE = {
    {0x00,"ROM ONLY"},
    {0x01,"MBC1"},
    {0x02,"MBC1+RAM"},
    {0x03,"MBC1+RAM+BATTERY"},
    {0x05,"MBC2"},
    {0x06,"MBC2+BATTERY"},
    {0x08,"ROM+RAM"},
    {0x09,"ROM+RAM+BATTERY"},
    {0x0B,"MMM01"},
    {0x0C,"MMM01+RAM"},
    {0x0D,"MMM01+RAM+BATTERY"},
    {0x0F,"MBC3+TIMER+BATTERY"},
    {0x10,"MBC3+TIMER+RAM+BATTERY"},
    {0x11,"MBC3"},
    {0x12,"MBC3+RAM"},
    {0x13,"MBC3+RAM+BATTERY"},
    {0x19,"MBC5"},
    {0x1A,"MBC5+RAM"},
    {0x1B,"MBC5+RAM+BATTERY"},
    {0x1C,"MBC5+RUMBLE"},
    {0x1D,"MBC5+RUMBLE+RAM"},
    {0x1E,"MBC5+RUMBLE+RAM+BATTERY"},
    {0x20,"MBC6"},
    {0x22,"MBC7+SENSOR+RUMBLE+RAM+BATTERY"},
    // Not supported rn
    {0xFC, "POCKET CAMERA"},
    {0xFD, "BANDAI TAMA5"},
    {0xFE, "HuC3"},
    {0xFF, "HuC1+RAM+BATTERY"}
};

static const std::map<uint16_t, std::string> LIC_CODE = {
    {0x00, "None"},
    {0x01, "Nintendo R&D1"},
    {0x08, "Capcom"},
    {0x13, "Electronic Arts"},
    {0x18, "Hudson Soft"},
    {0x19, "b-ai"},
    {0x20, "kss"},
    {0x22, "pow"},
    {0x24, "PCM Complete"},
    {0x25, "san-x"},
    {0x28, "Kemco Japan"},
    {0x29, "seta"},
    {0x30, "Viacom"},
    {0x31, "Nintendo"},
    {0x32, "Bandai"},
    {0x33, "Ocean/Acclaim"},
    {0x34, "Konami"},
    {0x35, "Hector"},
    {0x37, "Taito"},
    {0x38, "Hudson"},
    {0x39, "Banpresto"},
    {0x41, "Ubi Soft"},
    {0x42, "Atlus"},
    {0x44, "Malibu"},
    {0x46, "angel"},
    {0x47, "Bullet-Proof"},
    {0x49, "irem"},
    {0x50, "Absolute"},
    {0x51, "Acclaim"},
    {0x52, "Activision"},
    {0x53, "American sammy"},
    {0x54, "Konami"},
    {0x55, "Hi tech entertainment"},
    {0x56, "LJN"},
    {0x57, "Matchbox"},
    {0x58, "Mattel"},
    {0x59, "Milton Bradley"},
    {0x60, "Titus"},
    {0x61, "Virgin"},
    {0x64, "LucasArts"},
    {0x67, "Ocean"},
    {0x69, "Electronic Arts"},
    {0x70, "Infogrames"},
    {0x71, "Interplay"},
    {0x72, "Broderbund"},
    {0x73, "sculptured"},
    {0x75, "sci"},
    {0x78, "THQ"},
    {0x79, "Accolade"},
    {0x80, "misawa"},
    {0x83, "lozc"},
    {0x86, "Tokuma Shoten Intermedia"},
    {0x87, "Tsukuda Original"},
    {0x91, "Chunsoft"},
    {0x92, "Video system"},
    {0x93, "Ocean/Acclaim"},
    {0x95, "Varie"},
    {0x96, "Yonezawa/s’pal"},
    {0x97, "Kaneko"},
    {0x99, "Pack in soft"},
    {0xA4, "Konami (Yu-Gi-Oh!)"}
};

//{hexVal, romBanks} romBanks * 16KiB - so 2 Banks = 32KiB or 32KiB * (1 << value)
static const std::map<uint8_t, int> ROM_SIZE = { //Dont actually need romsize due to calculation
    {0x00, 2},
    {0x01, 4},
    {0x02, 8},
    {0x03, 16},
    {0x04, 32},
    {0x05, 64},
    {0x06, 128},
    {0x07, 256},
    {0x08, 512},
    //Unofficial sizes
    {0x52, 72},
    {0x53, 80},
    {0x54, 96}
};

//{hexVal, ramBanks} ramBanks * 8KiB so 4 Banks = 32KiB
static const std::map<uint8_t, int> RAM_SIZE = { //Dont actually need this map due to calculation
    {0x00, 0},
    {0x02, 1},
    {0x03, 4},
    {0x04, 16},
    {0x05, 8}
};

class Cart
{
    struct cartHeader
    {
        uint8_t entry[4];//4 bytes
        uint8_t logo[0x30];
        
        uint8_t title[16];
        //uint8_t manCode[0x04]; //Memory overlaps with title skipping for now because these 2 are only on color gameboy
        //uint8_t cgbFlag;
        uint16_t licCode;
        uint8_t sgbFlag;
        uint8_t cartType;
        uint8_t romSize;
        uint8_t ramSize;
        uint8_t dstCode;
        uint8_t oldLicCode;
        uint8_t romVersion;
        uint8_t checksum;
        uint16_t globalChecksum;
    };

    std::string m_filename;
    uint32_t m_romSize;
    std::vector<uint8_t> m_romData;
    cartHeader* m_romHeader;

public:

    Cart();
    ~Cart();

    bool loadCart(std::string);

    std::string cartTypeName();

    std::string cartLicName();

    std::string cartRamSize();

    bool calcChecksum();
};