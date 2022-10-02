#include "Text.hh"

#include <cppwebsite/common/Document.hh>
#include <cppwebsite/common/Escape.hh>

namespace cppwebsite::dom
{
    Text::Text(std::string content, EscapePolicy escapePolicy)
    : m_content(escapeForHtml(content, escapePolicy)) {}

    Text::~Text() = default;

    void
    Text::append(Document& document) const {
        document.append(m_content);
    }

    Text::ptr
    Text::create(std::string content) {
        return std::make_unique<Text>(std::move(content), EscapePolicy::Default);
    }

    Text::ptr
    Text::createRaw(std::string content) {
        return std::make_unique<Text>(std::move(content), EscapePolicy::EscapeWhitespace);
    }

} // namespace cppwebsite::dom
