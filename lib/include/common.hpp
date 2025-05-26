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

#define BIT(a, n) ((a & (1 << n)) ? 1 : 0) //If a reg bit and 1 bit shift by n is true then return 1 otherwise return 0

#define BIT_SET(a, n, on) { if (on) a |= (1 << n); else a &= ~(1 << n);}

#define BETWEEN(a, b, c) ((a >= b) && (a <= c))

inline std::ostream& operator<<(std::ostream& os, const uint8_t& obj) { 
    os << std::format("{:#x}", (uint8_t)obj);
    return os; 
}