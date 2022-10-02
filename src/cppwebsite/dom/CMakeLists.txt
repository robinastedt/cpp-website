add_namespaced_library(
    NAME dom
    SOURCES
        Class.cc
        DocumentObject.cc
        Id.cc
        Tag.cc
        Text.cc
    DEPENDS_INTERNAL
        common
)
