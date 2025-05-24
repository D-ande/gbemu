cmake_minimum_required(VERSION 3.28.3)

set(TARGET_NAME gbemulib)

set(TARGET_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/instruction.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cart.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/bus.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/emu.cpp
)

set(TARGET_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/common.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/instruction.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cpu.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cart.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/bus.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/include/emu.hpp
)

add_library(${TARGET_NAME} SHARED)

target_sources(${TARGET_NAME}
    PRIVATE
        ${TARGET_HEADERS}
        ${TARGET_SOURCES}
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)