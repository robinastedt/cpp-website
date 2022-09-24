#pragma once

#include <cppwebsite/pages/Page.hh>

namespace cppwebsite::pages
{
    class Index : public Page {
        std::string m_content;

    public:
        Index();

        ~Index() override;

        void handleRequest(const httplib::Request& request, httplib::Response& response) const override;
    };
} // namespace cppwebsite::pages
