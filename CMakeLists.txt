cmake_minimum_required(VERSION 3.28.3)

set(PROJECT_NAME gbemu)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDAR_REQUIRED True)

add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/gbemu/main.cpp
)

add_subdirectory(lib)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        gbemulib
)