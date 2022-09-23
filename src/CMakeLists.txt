project(cpp-website)

cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

# file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/webroot)
# 
# add_custom_command(
#     OUTPUT webroot/index.html.hh
#     COMMAND xxd -i webroot/index.html ${CMAKE_BINARY_DIR}/webroot/index.html.hh
#     DEPENDS webroot/index.html
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
# )
# 
# add_custom_target(generate_index_html
#     DEPENDS webroot/index.html.hh
# )

include_directories(
    ${CMAKE_SOURCE_DIR}
    # ${CMAKE_BINARY_DIR}
)

add_subdirectory(cppwebsite)



# add_dependencies(cpp-website
#     generate_index_html
# )