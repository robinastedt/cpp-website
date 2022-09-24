#include "Text.hh"

#include <cppwebsite/dom/Escape.hh>
#include <cppwebsite/dom/Document.hh>

namespace cppwebsite::dom
{
    Text::Text(std::string content)
    : m_content(escapeForHtml(content)) {}

    Text::~Text() = default;

    void
    Text::append(Document& document) const {
        document.append(m_content);
    }
} // namespace cppwebsite::dom
