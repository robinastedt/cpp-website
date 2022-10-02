#pragma once

#include <cppwebsite/pages/Page.hh>
#include <cppwebsite/pages/Css.hh>
#include <cppwebsite/dom/DocumentObject.hh>

namespace cppwebsite::pages
{
    class Index : public Page {
        std::unique_ptr<Css> m_styleSheetPage;  // temporary during initialization
        dom::DocumentObject::ptr m_dom;
        std::string m_content;

    public:
        Index();

        ~Index() override;

        void handleRequest(const httplib::Request& request, httplib::Response& response) const override;
    };
} // namespace cppwebsite::pages
