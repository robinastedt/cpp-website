#include "Style.hh"

#include <cppwebsite/common/Document.hh>

namespace cppwebsite::css
{

    Style::Style(Selector selector, Properties properties)
    : m_selector(std::move(selector))
    , m_properties(std::move(properties))
    {}

    void
    Style::append(Document& document) const {
        m_selector.append(document);
        document.append(" {\n");
        {
            Document::IndentScope indentScope{document.indent()};
            for (const Property& property : m_properties) {
                document.append(property.key)
                        .append(": ")
                        .append(property.value)
                        .append(";\n");
            }
        }
        document.append("}\n");
    }

} // namespace cppwebsite::css
