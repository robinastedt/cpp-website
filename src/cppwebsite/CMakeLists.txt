add_subdirectory(dom)
add_subdirectory(pages)

add_executable(cpp-website
    main.cc
)

target_link_libraries(cpp-website
    cpp-website-pages
)