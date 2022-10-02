#pragma once

#include <cppwebsite/css/Style.hh>

#include <vector>

namespace cppwebsite::css
{
    class StyleSheet {
        std::vector<Style> m_styles;

    public:
        StyleSheet();

        void add(Style style);
        void add(Selector selector, Properties properties);

        void append(Document& document) const;
    };
} // namespace cppwebsite::css
