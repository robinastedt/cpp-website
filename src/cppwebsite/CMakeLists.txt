add_subdirectory(common)
add_subdirectory(dom)
add_subdirectory(css)
add_subdirectory(pages)

add_executable(cpp-website
    main.cc
)

target_link_libraries(cpp-website
    cpp-website-common
    cpp-website-dom
    cpp-website-css
    cpp-website-pages
)