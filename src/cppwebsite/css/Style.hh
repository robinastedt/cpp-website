#pragma once

#include <cppwebsite/common/Property.hh>
#include <cppwebsite/dom/Tag.hh>
#include <cppwebsite/dom/Id.hh>
#include <cppwebsite/dom/Class.hh>
#include <cppwebsite/css/TagState.hh>


namespace cppwebsite::dom
{
    class Document;
} // namespace cppwebsite::dom


namespace cppwebsite::css
{
    class Style {
        friend class StyleSheet;

        Properties m_properties;
        std::string m_type;
        dom::Id m_id;
        dom::Class m_class;

    public:
        Style(Properties properties, const dom::Tag* tag, TagState state, dom::Id id, dom::Class clazz);

        void append(dom::Document& document) const;
    };
} // namespace cppwebsite::css
