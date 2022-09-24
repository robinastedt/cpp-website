#pragma once

#include <string>

namespace cppwebsite::dom
{
    class DocumentObject;

    class Document {
        size_t m_indentation;
        std::string m_content;

        Document();

    public:
        class IndentScope {
            friend class Document;
            Document& m_document;
            IndentScope(Document& document);

        public:
            ~IndentScope();
        };

        IndentScope indent();
        Document& append(std::string_view str);

        static std::string createPageContentFromDom(const DocumentObject& dom);
        
    };
} // namespace cppwebsite::dom
