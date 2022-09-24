#include "Index.hh"

#include <cppwebsite/dom/Tag.hh>
#include <cppwebsite/dom/Text.hh>
#include <cppwebsite/dom/Document.hh>
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
            // Title box
            std::vector<dom::DocumentObject::ptr> contactLinkChildren;
            contactLinkChildren.emplace_back(dom::Tag::createDiv("Robin Åstedt"));
            contactLinkChildren.emplace_back(dom::Tag::createDiv("Contact"));
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

            Properties bodyStyle {
                {"background-color", "#000000"},
                {"color", "#972322"},
                {"text-shadow", "3px 3px 3px #000000"}
            };

            styleSheetPage.getStyleSheet().addTagType(std::move(bodyStyle), *body);

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
    , m_content(dom::Document::createPageContentFromDom(*m_dom))
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
