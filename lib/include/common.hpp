#pragma once

#include <cstdint>
#include <iostream>
#include <exception>
#include <vector>
#include <map>
#include <string>
#include <format>
#include <cstring>

#if defined(__linux__)
#include <arpa/inet.h>
#endif

#define NOT_IMPL { std::cerr << "NOT YET IMPLEMENTED\n" << std::endl; exit(-1); }

inline std::ostream& operator<<(std::ostream& os, const uint8_t& obj) { 
    os << std::format("{:#x}", (uint8_t)obj);
    return os; 
}