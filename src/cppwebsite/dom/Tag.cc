#include "Tag.hh"

#include <cppwebsite/dom/Escape.hh>
#include <cppwebsite/dom/Text.hh>

namespace cppwebsite::dom
{
    Tag::Tag(std::string name, Properties properties, std::vector<ptr> children, ChildPolicy childPolicy)
    : m_name(std::move(name))
    , m_properties(std::move(properties))
    , m_children(std::move(children))
    , m_childPolicy(childPolicy)
    {}

    Tag::~Tag() = default;

    void
    Tag::append(std::string& document) const {
        document.append("<").append(m_name);
        for (const Property& property : m_properties) {
            document.append(" ")
                    .append(property.key)
                    .append("=\"")
                    .append(escapeForHtml(property.value))
                    .append("\"");
        }
        document.append(">");

        if (m_childPolicy == ChildPolicy::NewLine) {
            document.append("\n");
        }
        for (const ptr& child : m_children) {
            child->append(document);
            if (m_childPolicy == ChildPolicy::NewLine) {
                document.append("\n");
            }
        }

        document.append("</").append(m_name).append(">");
    }

    void
    Tag::addChild(std::unique_ptr<DocumentObject> child) {
        m_children.emplace_back(std::move(child));
    }

    void
    Tag::addChildren(std::vector<ptr> children) {
        if (m_children.empty()) {
            m_children = std::move(children);
        } else {
            for (ptr& child : children) {
                m_children.emplace_back(std::move(child));
            }
        }
    }

    Tag::ptr
    Tag::createHtml(std::vector<ptr> children) {
        return std::make_unique<Tag>("html", Properties{}, std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr
    Tag::createHeader(std::vector<ptr> children) {
        return std::make_unique<Tag>("header", Properties{}, std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr
    Tag::createTitle(std::string content) {
        std::vector<ptr> children;
        children.emplace_back(std::make_unique<Text>("title"));
        return std::make_unique<Tag>("title", Properties{}, std::move(children), ChildPolicy::Inline);
    }

    Tag::ptr
    Tag::createMeta(std::string name, std::string content) {
        Properties properties {
            {"name", std::move(name)},
            {"content", std::move(content)}
        };
        return std::make_unique<Tag>("meta", std::move(properties));
    }

    Tag::ptr
    Tag::createBody(std::vector<ptr> children) {
        return std::make_unique<Tag>("body", Properties{}, std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr Tag::createDiv(std::string id, ptr child, ChildPolicy childPolicy) {
        std::vector<ptr> children;
        children.emplace_back(std::move(child));
        return createDiv(std::move(id), std::move(children), childPolicy);
    }

    Tag::ptr
    Tag::createDiv(std::string id, std::vector<ptr> children, ChildPolicy childPolicy) {
        Properties properties {
            {"id", std::move(id)}
        };
        return std::make_unique<Tag>("div", std::move(properties), std::move(children), childPolicy);
    }

    Tag::ptr Tag::createDiv(std::string id, std::string text) {
        std::vector<ptr> children;
        children.emplace_back(std::make_unique<Text>(std::move(text)));
        return createDiv(std::move(id), std::move(children), ChildPolicy::Inline);
    }

    namespace
    {
        std::string
        linkPolicyProperty(Tag::LinkPolicy policy) {
            switch (policy) {
                case Tag::LinkPolicy::Self: return "_self";
                case Tag::LinkPolicy::NewTab: return "_blank";
            }
            throw std::runtime_error("Unhandled enum value: " + std::to_string((int)policy));
        }
    } // namespace
    

    Tag::ptr
    Tag::createLink(std::string path, std::vector<ptr> children, ChildPolicy childPolicy, LinkPolicy linkPolicy) {
        Properties properties {
            {"target", linkPolicyProperty(linkPolicy)},
            {"href", std::move(path)}
        };
        return std::make_unique<Tag>("a", std::move(properties), std::move(children), childPolicy);
    }

    Tag::ptr
    Tag::createLink(std::string path, std::string text, LinkPolicy linkPolicy) {
        std::vector<ptr> children;
        children.emplace_back(std::make_unique<Text>(std::move(text)));
        return createLink(std::move(path), std::move(children), ChildPolicy::Inline, linkPolicy);
    }

} // namespace cppwebsite::dom
