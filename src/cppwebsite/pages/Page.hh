#pragma once

#include <cppwebsite/httplibfwd.hh>

#include <string>

namespace cppwebsite::pages
{
    class Page {
        std::string m_path;

        virtual void handleRequest(const httplib::Request& request, httplib::Response& response) const = 0;
    public:
        static const char *const _htmlContentType;

        Page(std::string path);

        virtual ~Page();

        void registerServer(httplib::Server& server) const;

    };
} // namespace cppwebsite::pages
