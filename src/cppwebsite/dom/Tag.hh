#pragma once

#include <cppwebsite/dom/DocumentObject.hh>

#include <string>
#include <vector>
#include <memory>

namespace cppwebsite::dom
{
    class Tag : public DocumentObject {
    public:
        struct Property {
            std::string key;
            std::string value;
        };

        enum class ChildPolicy {
            Inline,
            NewLine
        };

        enum class LinkPolicy {
            Self,
            NewTab
        };

        using Properties = std::vector<Property>;

    private:
        std::string m_name;
        Properties m_properties;
        std::vector<DocumentObject::ptr> m_children;
        ChildPolicy m_childPolicy;

    public:
        Tag(std::string name, Properties properties, std::vector<ptr> children = {}, ChildPolicy childPolicy = {});
    
        ~Tag() override;

        void append(std::string& document) const override;

        void addChild(ptr child);
        void addChildren(std::vector<ptr> children);

        static ptr createHtml(std::vector<ptr> children);
        static ptr createHeader(std::vector<ptr> children);
        static ptr createTitle(std::string content);
        static ptr createMeta(std::string name, std::string content);
        static ptr createBody(std::vector<ptr> children);
        static ptr createDiv(std::string id, ptr child, ChildPolicy childPolicy);
        static ptr createDiv(std::string id, std::vector<ptr> children, ChildPolicy childPolicy);
        static ptr createDiv(std::string id, std::string text);
        static ptr createLink(std::string path, std::vector<ptr> children, ChildPolicy childPolicy, LinkPolicy linkPolicy = LinkPolicy::Self);
        static ptr createLink(std::string path, std::string text, LinkPolicy linkPolicy = LinkPolicy::Self);

    };
} // namespace cppwebsite::dom
