#pragma once

#include <cppwebsite/dom/DocumentObject.hh>

namespace cppwebsite::dom
{
    class Text : public DocumentObject {
        std::string m_content;

    public:
        Text(std::string content);
    
        ~Text() override;

        void append(Document& document) const override;
    };
} // namespace cppwebsite::dom
