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

        static ptr createHtml(std::vector<ptr> children = {});
        static ptr createHeader(std::vector<ptr> children = {});
        static ptr createTitle(std::string content);
        static ptr createMeta(std::string name, std::string content);
        static ptr createBody(std::vector<ptr> children = {});
    };
} // namespace cppwebsite::dom
