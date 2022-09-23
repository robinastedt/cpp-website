#include "Text.hh"

#include <cppwebsite/dom/Escape.hh>

namespace cppwebsite::dom
{
  

    Text::Text(std::string content)
    : m_content(escapeForHtml(content)) {}

    Text::~Text() = default;

    void
    Text::append(std::string& document) const {
        document.append(m_content);
    }
} // namespace cppwebsite::dom
