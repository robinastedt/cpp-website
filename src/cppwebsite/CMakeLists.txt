add_subdirectory(app)
add_subdirectory(common)
add_subdirectory(css)
add_subdirectory(dom)
add_subdirectory(pages)

add_namespaced_executable(
    NAME cppwebsite
    SOURCES
        main.cc
    DEPENDS_INTERNAL
        app
)
