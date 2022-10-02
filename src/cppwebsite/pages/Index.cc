#include "Index.hh"

#include <cppwebsite/common/Document.hh>

#include <cppwebsite/dom/Tag.hh>
#include <cppwebsite/dom/Text.hh>
#include <cppwebsite/dom/Id.hh>
#include <cppwebsite/dom/Class.hh>

#include <cppwebsite/css/StyleSheet.hh>

#include <cppwebsite/pages/Css.hh>

#include <httplib.h>

#include <memory>


namespace cppwebsite::pages
{
    namespace
    {
        auto createHeader(Css& styleSheetPage) {
            std::vector<dom::DocumentObject::ptr> children;
            children.emplace_back(dom::Tag::createTitle("Robin Åstedt"));
            children.emplace_back(dom::Tag::createMeta("keywords", "Robin Åstedt, Programming, Music, Poetry, C++, Java, C#, Projects"));
            children.emplace_back(dom::Tag::createMeta("author", "Robin Åstedt"));
            children.emplace_back(dom::Tag::createMeta("description", "Robin Åstedt: My personal website showcasing ongoing programming projects as well music and texts made by me."));
            auto styleSheetLink = std::make_unique<dom::Tag>("link");
            styleSheetLink->addProperty("rel", "stylesheet");
            styleSheetLink->addProperty("type", "text/css");
            styleSheetLink->addProperty("href", styleSheetPage.getPath());
            children.emplace_back(std::move(styleSheetLink));
            auto header = dom::Tag::createHeader(std::move(children));
            return header;
        }

        auto createBody(Css& styleSheetPage) {
            css::StyleSheet& styleSheet = styleSheetPage.getStyleSheet();

            // General styles
            Properties bodyStyle {
                {"background-color", "#000000"},
                {"color", "#972322"},
                {"text-shadow", "3px 3px 3px #000000"}
            };

            Properties linkUnvisitedStyle {
                {"color", "#972322"},
                {"text-description", "none"}
            };

            Properties linkVisitedStyle {
                {"color", "#972322"},
                {"text-description", "none"}
            };

            Properties linkHoverStyle {
                {"color", "#904848"},
                {"text-description", "none"}
            };

            Properties linkActiveStyle {
                {"color", "#900000"},
                {"text-description", "none"}
            };

            auto genericLink = dom::Tag::createLink("", "");
            css::Selector linkSelector = css::Selector{}.matchTag(*genericLink);
            css::Selector linkUnvisitedSelector = css::Selector{}.matchTag(*genericLink, css::TagState::LinkUnvisited);
            css::Selector linkVisitedSelector = css::Selector{}.matchTag(*genericLink, css::TagState::LinkVisisted);
            css::Selector linkHoverSelector = css::Selector{}.matchTag(*genericLink, css::TagState::ActionHover);
            css::Selector linkActiveSelector = css::Selector{}.matchTag(*genericLink, css::TagState::ActionActive);
            styleSheet.add(linkUnvisitedSelector, linkUnvisitedStyle);
            styleSheet.add(linkVisitedSelector, linkVisitedStyle);
            styleSheet.add(linkHoverSelector, linkHoverStyle);
            styleSheet.add(linkActiveSelector, linkActiveStyle);

            // Title box
            std::vector<dom::DocumentObject::ptr> contactLinkChildren;
            auto contactLinkContent1 = dom::Tag::createDiv("Robin Åstedt");
            contactLinkContent1->setClass(dom::Class::createNew());
            auto contactLinkContent2 = dom::Tag::createDiv("Contact");
            contactLinkContent2->setClass(dom::Class::createNew());

            Properties contactLink1DefaultStyle {
                {"display", "inline"}
            };
            Properties contactLink2DefaultStyle {
                {"display", "none"}
            };
            Properties contactLink1HoverStyle {
                {"display", "none"}
            };
            Properties contactLink2HoverStyle {
                {"display", "inline"},
                {"padding-left", "200px"},
                {"padding-right", "200px"}
            };

            styleSheet.add(linkSelector.matchClass(*contactLinkContent1), std::move(contactLink1DefaultStyle));
            styleSheet.add(linkSelector.matchClass(*contactLinkContent2) ,std::move(contactLink2DefaultStyle));
            styleSheet.add(linkHoverSelector.matchClass(*contactLinkContent1), std::move(contactLink1HoverStyle));
            styleSheet.add(linkHoverSelector.matchClass(*contactLinkContent2), std::move(contactLink2HoverStyle));

            contactLinkChildren.emplace_back(std::move(contactLinkContent1));
            contactLinkChildren.emplace_back(std::move(contactLinkContent2));
            auto contactLink = dom::Tag::createLink(
                "mailto:robin.astedt@gmail.com",
                std::move(contactLinkChildren),
                dom::ChildPolicy::Inline,
                dom::LinkPolicy::NewTab
            );

            auto titleBox = dom::Tag::createDiv(std::move(contactLink), dom::ChildPolicy::NewLine);

            // Link box
            auto musicLink = dom::Tag::createLink("music", "Music");
            auto projectsLink = dom::Tag::createLink("projects", "Projects");
            auto textLink = dom::Tag::createLink("text", "Text");
            std::string linkBoxDelimiter = " | ";
            std::vector<dom::DocumentObject::ptr> linkBoxChildren;
            linkBoxChildren.emplace_back(std::move(musicLink));
            linkBoxChildren.emplace_back(std::make_unique<dom::Text>(linkBoxDelimiter));
            linkBoxChildren.emplace_back(std::move(projectsLink));
            linkBoxChildren.emplace_back(std::make_unique<dom::Text>(linkBoxDelimiter));
            linkBoxChildren.emplace_back(std::move(textLink));
            auto linkBoxContent = dom::Tag::createDiv(std::move(linkBoxChildren), dom::ChildPolicy::Inline);
            auto linkBox = dom::Tag::createDiv(std::move(linkBoxContent), dom::ChildPolicy::NewLine);

            // Main box
            std::vector<dom::DocumentObject::ptr> mainBoxChildren;
            mainBoxChildren.emplace_back(std::move(titleBox));
            mainBoxChildren.emplace_back(std::move(linkBox));
            auto mainBox = dom::Tag::createDiv(std::move(mainBoxChildren), dom::ChildPolicy::NewLine);

            // Whole page box
            auto wholePageBox = dom::Tag::createDiv(std::move(mainBox), dom::ChildPolicy::NewLine);

            std::vector<dom::DocumentObject::ptr> children;
            children.emplace_back(std::move(wholePageBox));
            auto body = dom::Tag::createBody(std::move(children));
            styleSheet.add(css::Selector{}.matchTag(*body), std::move(bodyStyle));

            return body;
        }

        auto
        createDom(Css& styleSheetPage) {
            std::vector<dom::DocumentObject::ptr> children;
            children.emplace_back(createHeader(styleSheetPage));
            children.emplace_back(createBody(styleSheetPage));
            return dom::Tag::createHtml(std::move(children));
        }
    } // namespace
    

    Index::Index()
    : Page("/")
    , m_styleSheetPage(std::make_unique<Css>("/css/front.css"))
    , m_dom(createDom(*m_styleSheetPage))
    , m_content(Document::createPageContent(*m_dom))
    {
        m_styleSheetPage->computeContent();
        addSubpage(std::move(m_styleSheetPage));
    }

    Index::~Index() = default;

    void
    Index::handleRequest(const httplib::Request& request, httplib::Response& response) const {
        response.set_content(m_content, _htmlContentType);
    }

} // namespace cppwebsite::pages
