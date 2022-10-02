add_namespaced_library(
    NAME css
    SOURCES
        Selector.cc
        Style.cc
        StyleSheet.cc
    DEPENDS_INTERNAL
        common
        dom
)
