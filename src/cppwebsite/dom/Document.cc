#include "Document.hh"

#include <cppwebsite/dom/DocumentObject.hh>

#include <cassert>

namespace cppwebsite::dom
{
    Document::Document()
    : m_indentation(0)
    , m_content()
    {}


    Document::IndentScope::IndentScope(Document& document)
    : m_document(document)
    {
        m_document.m_indentation += 1;
    }

    Document::IndentScope::~IndentScope() {
        assert(m_document.m_indentation > 0);
        m_document.m_indentation -= 1;
    }


    Document::IndentScope
    Document::indent() {
        return IndentScope{*this};
    }

    Document&
    Document::append(std::string_view str) {
        if (*m_content.crbegin() == '\n') {
            static constexpr char indentationString[] = "    ";
            for (size_t level = 0; level < m_indentation; ++level) {
                m_content.append(indentationString);
            }
        }
        m_content.append(str);
        return *this;
    }

    const std::string&
    Document::getContent() const {
        return m_content;
    }

    std::string
    Document::createPageContentFromDom(const DocumentObject& dom) {
        Document document;
        dom.append(document);
        return document.m_content;
    }

} // namespace cppwebsite::dom
