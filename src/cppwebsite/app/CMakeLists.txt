add_namespaced_library(
    NAME app
    SOURCES
        App.cc
        Options.cc
    DEPENDS_INTERNAL
        pages
    DEPENDS
        httplib::httplib
        boost_program_options
)
