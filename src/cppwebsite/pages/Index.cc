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
            std::vector<dom::DocumentObject::ptr> children;
            children.emplace_back(std::make_unique<dom::Text>("Hello world!"));
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
