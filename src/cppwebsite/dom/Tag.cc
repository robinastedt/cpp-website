#include "Tag.hh"

#include <cppwebsite/dom/Escape.hh>
#include <cppwebsite/dom/Text.hh>
#include <cppwebsite/dom/Id.hh>
#include <cppwebsite/dom/Class.hh>

#include <cppwebsite/common/Document.hh>

#include <cassert>

namespace cppwebsite::dom
{
    Tag::Tag(std::string type, DocumentObjects children, ChildPolicy childPolicy)
    : m_type(std::move(type))
    , m_id(Id::createNew())
    , m_class(Class::anonymous())
    , m_properties()
    , m_children(std::move(children))
    , m_childPolicy(childPolicy)
    {}

    Tag::~Tag() = default;

    const std::string&
    Tag::getType() const {
        return m_type;
    }

    Id
    Tag::getId() const {
        return m_id;
    }

    Class
    Tag::getClass() const {
        return m_class;
    }

    void
    Tag::setClass(Class clazz) {
        m_class = clazz;
    }

    void
    Tag::addProperty(Property property) {
        assert(property.key != "id");    // These have special handling
        assert(property.key != "class");
        m_properties.emplace_back(std::move(property));
    }

    void
    Tag::addProperty(std::string key, std::string value) {
        addProperty(Property{std::move(key), std::move(value)});
    }

    namespace
    {
        void appendProperty(Document& document, const Property& property) {
            document.append(" ")
                    .append(property.key)
                    .append("=\"")
                    .append(escapeForHtml(property.value))
                    .append("\"");
        }
    } // namespace
    

    void
    Tag::append(Document& document) const {
        document.append("<").append(m_type);
        appendProperty(document, m_id.getProperty());
        if (!m_class.isAnonymous()) {
            appendProperty(document, m_class.getProperty());
        }
        for (const Property& property : m_properties) {
            appendProperty(document, property);
        }
        document.append(">");

        if (m_childPolicy == ChildPolicy::NewLine) {
            document.append("\n");
        }
        for (const DocumentObject::ptr& child : m_children) {
            Document::IndentScope indent = document.indent();
            child->append(document);
            if (m_childPolicy == ChildPolicy::NewLine) {
                document.append("\n");
            }
        }

        document.append("</").append(m_type).append(">");
    }

    void
    Tag::addChild(DocumentObject::ptr child) {
        m_children.emplace_back(std::move(child));
    }

    void
    Tag::addChildren(DocumentObjects children) {
        if (m_children.empty()) {
            m_children = std::move(children);
        } else {
            for (DocumentObject::ptr& child : children) {
                m_children.emplace_back(std::move(child));
            }
        }
    }

    Tag::ptr
    Tag::createHtml(DocumentObjects children) {
        return std::make_unique<Tag>("html", std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr
    Tag::createHeader(DocumentObjects children) {
        return std::make_unique<Tag>("header",  std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr
    Tag::createTitle(std::string content) {
        DocumentObjects children;
        children.emplace_back(std::make_unique<Text>(std::move(content)));
        return std::make_unique<Tag>("title", std::move(children), ChildPolicy::Inline);
    }

    Tag::ptr
    Tag::createMeta(std::string name, std::string content) {
        auto meta = std::make_unique<Tag>("meta");
        meta->addProperty("name", std::move(name));
        meta->addProperty("content", std::move(content));
        return meta;
    }

    Tag::ptr
    Tag::createBody(DocumentObject::ptr child) {
        DocumentObjects children;
        children.emplace_back(std::move(child));
        return createBody(std::move(children));
    }

    Tag::ptr
    Tag::createBody(DocumentObjects children) {
        return std::make_unique<Tag>("body", std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr
    Tag::createDiv(DocumentObject::ptr child, ChildPolicy childPolicy) {
        DocumentObjects children;
        children.emplace_back(std::move(child));
        return createDiv(std::move(children), childPolicy);
    }

    Tag::ptr
    Tag::createDiv(DocumentObjects children, ChildPolicy childPolicy) {
        return std::make_unique<Tag>("div", std::move(children), childPolicy);
    }

    Tag::ptr Tag::createDiv(std::string text) {
        return createDiv(std::make_unique<Text>(std::move(text)), ChildPolicy::Inline);
    }

    namespace
    {
        std::string
        linkPolicyProperty(LinkPolicy policy) {
            switch (policy) {
                case LinkPolicy::Self: return "_self";
                case LinkPolicy::NewTab: return "_blank";
            }
            throw std::runtime_error("Unhandled enum value: " + std::to_string((int)policy));
        }
    } // namespace
    

    Tag::ptr
    Tag::createLink(std::string path, DocumentObjects children, ChildPolicy childPolicy, LinkPolicy linkPolicy) {
        auto link = std::make_unique<Tag>("a", std::move(children), childPolicy);
        link->addProperty("target", linkPolicyProperty(linkPolicy));
        link->addProperty("href", std::move(path));
        return link;
    }

    Tag::ptr
    Tag::createLink(std::string path, std::string text, LinkPolicy linkPolicy) {
        DocumentObjects children;
        children.emplace_back(std::make_unique<Text>(std::move(text)));
        return createLink(std::move(path), std::move(children), ChildPolicy::Inline, linkPolicy);
    }

} // namespace cppwebsite::dom
