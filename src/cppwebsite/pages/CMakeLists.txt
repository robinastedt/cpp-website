add_library(cpp-website-pages
    Index.cc
    Page.cc
)

target_link_libraries(cpp-website-pages
    cpp-website-dom
)