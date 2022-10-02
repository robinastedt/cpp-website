cmake_minimum_required(VERSION 3.22)

project(cppwebsite
    DESCRIPTION "Robin Åstedt's personal website, implemented in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

find_package(httplib REQUIRED)

include(cmake/targets.cmake)

add_subdirectory(cppwebsite)
