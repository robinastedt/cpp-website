#include "Css.hh"

#include <cppwebsite/common/Document.hh>
#include <cppwebsite/css/StyleSheet.hh>

#include <httplib.h>

namespace cppwebsite::pages
{
    Css::Css(std::string path)
    : Page(std::move(path))
    , m_styleSheet()
    , m_content()
    {}

    Css::~Css() = default;

    void
    Css::handleRequest(const httplib::Request& request, httplib::Response& response) const {
        response.set_content(m_content, _cssContentType);
    };

    void
    Css::computeContent() {
        m_content = Document::createPageContent(m_styleSheet);
    }

    css::StyleSheet&
    Css::getStyleSheet() {
        return m_styleSheet;
    }
} // namespace cppwebsite::pages
