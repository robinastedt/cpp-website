#pragma once

#include <cppwebsite/dom/DocumentObject.hh>
#include <cppwebsite/common/Escape.hh>

namespace cppwebsite::dom
{
    class Text : public DocumentObject {
        std::string m_content;

    public:
        Text(std::string content, EscapePolicy escapePolicy = EscapePolicy::Default);
    
        ~Text() override;

        using ptr = std::unique_ptr<Text>;

        static ptr create(std::string content);
        static ptr createRaw(std::string content);

        void append(Document& document) const override;
    };
} // namespace cppwebsite::dom
