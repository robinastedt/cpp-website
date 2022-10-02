#include "Selector.hh"

#include <cppwebsite/dom/Tag.hh>
#include <cppwebsite/common/Document.hh>

#include <ranges>

namespace cppwebsite::css
{
    Selector::Selector()
    : m_tag()
    , m_id(dom::Id::anonymous())
    , m_class(dom::Class::anonymous())
    {}

    namespace
    {
        std::string_view
        getStateSelector(TagState state) {
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
    } // namespace

    Selector
    Selector::matchTag(const dom::Tag& tag, TagState state) const {
        Selector copy {*this};
        copy.m_tag = tag.getType();
        copy.m_tag.append(getStateSelector(state));
        return copy;
    }

    Selector
    Selector::matchId(const dom::Tag& tag) const {
        Selector copy {*this};
        copy.m_id = tag.getId();
        return *this;
    }

    Selector
    Selector::matchClass(const dom::Tag& tag) const {
        Selector copy {*this};
        copy.m_class = tag.getClass();
        return copy;
    }

    void
    Selector::append(Document& document) const {
        std::vector<std::string> parts;

        if (!m_tag.empty()) {
            parts.emplace_back(m_tag);
        }
        if (!m_id.isAnonymous()) {
            parts.emplace_back("#" + m_id.getProperty().value);
        }
        if (!m_class.isAnonymous()) {
            parts.emplace_back("." + m_class.getProperty().value);
        }

        if (parts.empty()) {
            throw std::invalid_argument("Can not append empty selector to document.");
        }

        document.append(parts.front());
        for (const std::string& part : std::views::drop(parts, 1)) {
            document.append(" ").append(part);
        }
    }
} // namespace cppwebsite::css


