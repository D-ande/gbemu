cmake_minimum_required(VERSION 3.28.3)

set(TARGET_NAME gbemulib)

set(TARGET_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cart.cpp
)

set(TARGET_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cart.hpp
)

add_library(${TARGET_NAME} SHARED)

target_sources(${TARGET_NAME}
    PRIVATE
        ${TARGET_SOURCES}
        ${TARGET_HEADERS}
)

target_include_directories(${TARGET_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)