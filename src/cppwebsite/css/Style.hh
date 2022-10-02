#pragma once

#include <cppwebsite/common/Property.hh>
#include <cppwebsite/css/Selector.hh>

namespace cppwebsite
{
    class Document;
} // namespace cppwebsite


namespace cppwebsite::css
{
    class Style {
        Selector m_selector;
        Properties m_properties;

    public:
        Style(Selector selector, Properties properties);

        void append(Document& document) const;
    };
} // namespace cppwebsite::css
