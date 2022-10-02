#pragma once

#include <cppwebsite/css/TagState.hh>
#include <cppwebsite/dom/Id.hh>
#include <cppwebsite/dom/Class.hh>

#include <string>

namespace cppwebsite
{
    class Document;

    namespace dom
    {
        class Tag;
    } // namespace dom

    namespace css
    {
        class Selector {
            std::string m_tag;
            dom::Id m_id;
            dom::Class m_class;

        public:
            Selector();

            Selector matchTag(const dom::Tag& tag, TagState state = TagState::Default) const;
            Selector matchId(const dom::Tag& tag) const;
            Selector matchClass(const dom::Tag& tag) const;

            void append(Document& document) const;
        };
    } // namespace css
} // namespace cppwebsite


