add_library(cpp-website-pages
    Css.cc
    Index.cc
    Page.cc
)

target_link_libraries(cpp-website-pages
    cpp-website-dom
    cpp-website-css
)