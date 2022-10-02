cmake_minimum_required(VERSION 3.22)

project(cppwebsite
    DESCRIPTION "Robin Åstedt's personal website, implemented in C++"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

find_package(httplib REQUIRED)
find_package(Boost REQUIRED COMPONENTS program_options)

include_directories(
    ${CMAKE_SOURCE_DIR}
)

include(cmake/targets.cmake)

add_subdirectory(cppwebsite)
