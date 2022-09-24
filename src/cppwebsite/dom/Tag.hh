#pragma once

#include <cppwebsite/dom/DocumentObject.hh>
#include <cppwebsite/dom/ChildPolicy.hh>
#include <cppwebsite/dom/LinkPolicy.hh>
#include <cppwebsite/dom/Id.hh>
#include <cppwebsite/dom/Class.hh>

#include <cppwebsite/common/Property.hh>

#include <string>
#include <vector>
#include <memory>

namespace cppwebsite::dom
{
    class Id;
    class Class;

    class Tag : public DocumentObject {
        std::string m_type;
        Id m_id;
        Class m_class;
        Properties m_properties;
        DocumentObjects m_children;
        ChildPolicy m_childPolicy;

    public:
        using ptr = std::unique_ptr<Tag>;

        Tag(std::string type, DocumentObjects children = {}, ChildPolicy childPolicy = {});
    
        ~Tag() override;

        const std::string& getType() const;
        Id getId() const;
        Class getClass() const;
        void setClass(Class clazz);
        void addProperty(Property property);
        void addProperty(std::string key, std::string value);

        void append(Document& document) const override;

        void addChild(DocumentObject::ptr child);
        void addChildren(DocumentObjects children);

        static ptr createHtml(DocumentObjects children);
        static ptr createHeader(DocumentObjects children);
        static ptr createTitle(std::string content);
        static ptr createMeta(std::string name, std::string content);
        static ptr createBody(DocumentObjects children);
        static ptr createDiv(DocumentObject::ptr child, ChildPolicy childPolicy);
        static ptr createDiv(DocumentObjects children, ChildPolicy childPolicy);
        static ptr createDiv(std::string text);
        static ptr createLink(std::string path, DocumentObjects children, ChildPolicy childPolicy, LinkPolicy linkPolicy = LinkPolicy::Self);
        static ptr createLink(std::string path, std::string text, LinkPolicy linkPolicy = LinkPolicy::Self);

    };


} // namespace cppwebsite::dom
