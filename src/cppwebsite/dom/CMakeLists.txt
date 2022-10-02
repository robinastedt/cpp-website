add_library(cpp-website-dom STATIC
    Class.cc
    DocumentObject.cc
    Id.cc
    Tag.cc
    Text.cc
)

target_link_libraries(cpp-website-dom
    cpp-website-common
)