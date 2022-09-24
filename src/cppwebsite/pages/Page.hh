#pragma once

#include <cppwebsite/httplibfwd.hh>

#include <string>
#include <memory>
#include <vector>

namespace cppwebsite::pages
{
    class Page {
    public:
        using ptr = std::unique_ptr<Page>;

    private:
        std::string m_path;
        std::vector<ptr> m_subPages;

        virtual void handleRequest(const httplib::Request& request, httplib::Response& response) const = 0;
    public:
        static const char *const _htmlContentType;
        static const char *const _cssContentType;

        void addSubpage(ptr page);

        Page(std::string path);

        virtual ~Page();

        void registerServer(httplib::Server& server) const;

        const std::string& getPath() const;

    };
} // namespace cppwebsite::pages
