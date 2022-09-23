#pragma once

#include <cppwebsite/dom/DocumentObject.hh>
#include <cppwebsite/dom/ChildPolicy.hh>
#include <cppwebsite/dom/LinkPolicy.hh>
#include <cppwebsite/dom/Property.hh>

#include <string>
#include <vector>
#include <memory>

namespace cppwebsite::dom
{
    class Tag : public DocumentObject {
        std::string m_name;
        Properties m_properties;
        DocumentObjects m_children;
        ChildPolicy m_childPolicy;

    public:
        Tag(std::string name, Properties properties, DocumentObjects children = {}, ChildPolicy childPolicy = {});
    
        ~Tag() override;

        void append(std::string& document) const override;

        void addChild(ptr child);
        void addChildren(DocumentObjects children);

        static ptr createHtml(DocumentObjects children);
        static ptr createHeader(DocumentObjects children);
        static ptr createTitle(std::string content);
        static ptr createMeta(std::string name, std::string content);
        static ptr createBody(DocumentObjects children);
        static ptr createDiv(std::string id, ptr child, ChildPolicy childPolicy);
        static ptr createDiv(std::string id, DocumentObjects children, ChildPolicy childPolicy);
        static ptr createDiv(std::string id, std::string text);
        static ptr createLink(std::string path, DocumentObjects children, ChildPolicy childPolicy, LinkPolicy linkPolicy = LinkPolicy::Self);
        static ptr createLink(std::string path, std::string text, LinkPolicy linkPolicy = LinkPolicy::Self);

    };


} // namespace cppwebsite::dom
