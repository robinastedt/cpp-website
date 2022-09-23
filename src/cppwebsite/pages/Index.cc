#include "Index.hh"

#include <cppwebsite/dom/Tag.hh>
#include <cppwebsite/dom/Text.hh>

#include <httplib.h>

#include <memory>


namespace cppwebsite::pages
{
    namespace
    {
        auto createHeader() {
            std::vector<dom::DocumentObject::ptr> children;
            children.emplace_back(dom::Tag::createTitle("Robin Åstedt"));
            children.emplace_back(dom::Tag::createMeta("keywords", "Robin Åstedt, Programming, Music, Poetry, C++, Java, C#, Projects"));
            children.emplace_back(dom::Tag::createMeta("author", "Robin Åstedt"));
            children.emplace_back(dom::Tag::createMeta("description", "Robin Åstedt: My personal website showcasing ongoing programming projects as well music and texts made by me."));
            auto header = dom::Tag::createHeader(std::move(children));
            return header;
        }

        auto createBody() {
            // Title box
            std::vector<dom::DocumentObject::ptr> contactLinkChildren;
            contactLinkChildren.emplace_back(dom::Tag::createDiv("title1", "Robin Åstedt"));
            contactLinkChildren.emplace_back(dom::Tag::createDiv("title2", "Contact"));
            auto contactLink = dom::Tag::createLink(
                "mailto:robin.astedt@gmail.com",
                std::move(contactLinkChildren),
                dom::ChildPolicy::Inline,
                dom::LinkPolicy::NewTab
            );
            auto titleBox = dom::Tag::createDiv("titleBox", std::move(contactLink), dom::ChildPolicy::NewLine);

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
            auto linkBox = dom::Tag::createDiv("linkBox", std::move(linkBoxChildren), dom::ChildPolicy::Inline);

            // Main box
            std::vector<dom::DocumentObject::ptr> mainBoxChildren;
            mainBoxChildren.emplace_back(std::move(titleBox));
            mainBoxChildren.emplace_back(std::move(linkBox));
            auto mainBox = dom::Tag::createDiv("mainBox", std::move(mainBoxChildren), dom::ChildPolicy::NewLine);

            // Whole page box
            auto wholePageBox = dom::Tag::createDiv("wholepageBox", std::move(mainBox), dom::ChildPolicy::NewLine);

            std::vector<dom::DocumentObject::ptr> children;
            children.emplace_back(std::move(wholePageBox));
            return dom::Tag::createBody(std::move(children));
        }

        auto createHtml() {
            std::vector<dom::DocumentObject::ptr> children;
            children.emplace_back(createHeader());
            children.emplace_back(createBody());
            return dom::Tag::createHtml(std::move(children));
        }

        std::string
        createDocument() {
            std::string document;
            createHtml()->append(document);
            return document;
        }
    } // namespace
    

    Index::Index()
    : Page("/")
    , m_document(createDocument())
    {}

    Index::~Index() = default;

    void
    Index::handleRequest(const httplib::Request& request, httplib::Response& response) const {
        response.set_content(m_document, _htmlContentType);
    }
} // namespace cppwebsite::pages
