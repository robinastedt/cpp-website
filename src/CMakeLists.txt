cmake_minimum_required(VERSION 3.22)

project(cpp-website
    DESCRIPTION "Robin Åstedt's personal website, implemented in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

add_subdirectory(cppwebsite)
