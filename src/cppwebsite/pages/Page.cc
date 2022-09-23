#include "Page.hh"

#include <httplib.h>

namespace cppwebsite::pages
{
        const char *const Page::_htmlContentType = "text/html; charset=UTF-8";

        Page::Page(std::string path)
        : m_path(std::move(path))
        {}

        Page::~Page() = default;

        void
        Page::registerServer(httplib::Server& server) const {
            server.Get(m_path, [this](const httplib::Request& request, httplib::Response& response){
                handleRequest(request, response);
            });
        }


} // namespace cppwebsite::pages
