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

        const bool hasChildren = !m_children.empty();
        if (hasChildren) {
            document.append("\n");
        }
        for (const ptr& child : m_children) {
            child->append(document);
            if (hasChildren) {
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

    Tag::ptr Tag::createHtml(std::vector<ptr> children) {
        return std::make_unique<Tag>("html", Properties{}, std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr Tag::createHeader(std::vector<ptr> children) {
        return std::make_unique<Tag>("header", Properties{}, std::move(children), ChildPolicy::NewLine);
    }

    Tag::ptr Tag::createTitle(std::string content) {
        std::vector<ptr> children;
        children.emplace_back(std::make_unique<Text>("title"));
        return std::make_unique<Tag>("title", Properties{}, std::move(children), ChildPolicy::Inline);
    }

    Tag::ptr Tag::createMeta(std::string name, std::string content) {
        Properties properties {
            {"name", std::move(name)},
            {"content", std::move(content)}
        };
        return std::make_unique<Tag>("meta", std::move(properties));
    }

    Tag::ptr Tag::createBody(std::vector<ptr> children) {
        return std::make_unique<Tag>("body", Properties{}, std::move(children), ChildPolicy::NewLine);
    }

} // namespace cppwebsite::dom
