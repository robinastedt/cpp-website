#pragma once

#include <cppwebsite/pages/Page.hh>
#include <cppwebsite/css/StyleSheet.hh>

namespace cppwebsite::pages
{
    class Css : public Page {
        css::StyleSheet m_styleSheet;
        std::string m_content;

    public:
        Css(std::string path);

        ~Css() override;

        void handleRequest(const httplib::Request& request, httplib::Response& response) const override;

        void computeContent();
        css::StyleSheet& getStyleSheet();
    };
} // namespace cppwebsite::pages
