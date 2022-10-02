add_library(cpp-website-css
    Selector.cc
    Style.cc
    StyleSheet.cc
)

target_link_libraries(cpp-website-css
    cpp-website-common
    cpp-website-dom
)