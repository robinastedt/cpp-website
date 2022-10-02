add_subdirectory(common)
add_subdirectory(dom)
add_subdirectory(css)
add_subdirectory(pages)

add_namespaced_executable(
    NAME cppwebsite
    SOURCES
        main.cc
    DEPENDS_INTERNAL
        pages
    DEPENDS
        httplib::httplib
)
