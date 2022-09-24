#include "StyleSheet.hh"

#include <stdexcept>

namespace cppwebsite::css
{
    StyleSheet::StyleSheet()
    : m_styles()
    {}

    void
    StyleSheet::addUniqueTag(Properties properties, const dom::Tag& tag, TagState state) {
        m_styles.emplace_back(std::move(properties), &tag, state, tag.getId(), dom::Class::anonymous());
    }

    void
    StyleSheet::addTagType(Properties properties, const dom::Tag& tag, TagState state) {
        m_styles.emplace_back(std::move(properties), &tag, state, dom::Id::anonymous(), dom::Class::anonymous());
    }

    void
    StyleSheet::addClass(Properties properties, const dom::Class& clazz, TagState state) {
        m_styles.emplace_back(std::move(properties), nullptr, state, dom::Id::anonymous(), clazz);
    }

    void
    StyleSheet::append(Document& document) const {
        for (const Style& style : m_styles) {
            style.append(document);
        }
    }
} // namespace cppwebsite::css
