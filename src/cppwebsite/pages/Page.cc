#include "Page.hh"

#include <httplib.h>

namespace cppwebsite::pages
{
        const char *const Page::_htmlContentType = "text/html; charset=UTF-8";
        const char *const Page::_cssContentType = "text/css; charset=UTF-8";

        Page::Page(std::string path)
        : m_path(std::move(path))
        {}

        Page::~Page() = default;

        void
        Page::registerServer(httplib::Server& server) const {
            server.Get(m_path, [this](const httplib::Request& request, httplib::Response& response){
                handleRequest(request, response);
            });
            for (const ptr& page : m_subPages) {
                page->registerServer(server);
            }
        }

        void
        Page::addSubpage(ptr page) {
            m_subPages.emplace_back(std::move(page));
        }

        const std::string&
        Page::getPath() const {
            return m_path;
        }


} // namespace cppwebsite::pages
