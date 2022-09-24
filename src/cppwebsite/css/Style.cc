#include "Style.hh"

#include <cppwebsite/common/Document.hh>

#include <string>

namespace cppwebsite::css
{
    namespace
    {
        std::string_view
        getTypeSelector(TagState state) {
            switch (state) {
                case TagState::Default: return "";
                case TagState::LinkUnvisited: return ":link";
                case TagState::LinkVisisted: return ":visited";
                case TagState::ActionHover: return ":hover";
                case TagState::ActionActive: return ":active";
                case TagState::ActionFocus: return ":focus";
            }
            throw std::invalid_argument("Invalid TagState value: " + std::to_string((int)state));
        }

        std::string
        getTypeSelector(const dom::Tag* tag, TagState state) {
            std::string selector;
            if (tag) {
                selector += tag->getType();
            }
            selector.append(getTypeSelector(state));
            return selector;
        }
    } // namespace

    Style::Style(Properties properties, const dom::Tag* tag, TagState state, dom::Id id, dom::Class clazz)
    : m_properties(std::move(properties))
    , m_type(getTypeSelector(tag, state))
    , m_id(id)
    , m_class(clazz)
    {}

    void
    Style::append(Document& document) const {
        std::string selector;
        if (!m_type.empty()) {
            selector.append(m_type).append(" ");
        }
        if (!m_id.isAnonymous()) {
            selector.append(m_id.getProperty().value).append(" ");
        }
        if (!m_class.isAnonymous()) {
            selector.append(m_class.getProperty().value).append(" ");
        }
        if (selector.empty()) {
            throw std::invalid_argument("Can not append style to document as it has no selector!");
        }
        document.append(selector).append("{\n");
        {
            Document::IndentScope indentScope{document.indent()};
            for (const Property& property : m_properties) {
                document.append(property.key)
                        .append(": ")
                        .append(property.value)
                        .append(";\n");
            }
        }
        document.append("}\n");
    }

} // namespace cppwebsite::css
