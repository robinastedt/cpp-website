#pragma once

#include <string>

namespace cppwebsite
{
    class Document {
        size_t m_indentation;
        std::string m_content;

    public:
        Document();

        class IndentScope {
            friend class Document;
            Document& m_document;
            IndentScope(Document& document);

        public:
            ~IndentScope();
        };

        IndentScope indent();
        Document& append(std::string_view str);

        const std::string& getContent() const;

        template<typename T>
        static std::string createPageContent(const T& obj) {
            Document document;
            obj.append(document);
            return document.getContent();
        }
    };
} // namespace cppwebsite
