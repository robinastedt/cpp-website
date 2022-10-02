add_namespaced_library(
    NAME pages
    SOURCES
        Css.cc
        Index.cc
        Page.cc
    DEPENDS_INTERNAL
        css
        dom
        common
    DEPENDS
        httplib::httplib
)
