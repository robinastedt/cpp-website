#include "StyleSheet.hh"

namespace cppwebsite::css
{
    StyleSheet::StyleSheet()
    : m_styles()
    {}

    void
    StyleSheet::add(Style style) {
        m_styles.emplace_back(std::move(style));
    }

    void
    StyleSheet::add(Selector selector, Properties properties) {
        m_styles.emplace_back(std::move(selector), std::move(properties));
    }

    void
    StyleSheet::append(Document& document) const {
        for (const Style& style : m_styles) {
            style.append(document);
        }
    }
} // namespace cppwebsite::css
