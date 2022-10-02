#include "App.hh"

#include <cppwebsite/pages/Index.hh>

#include <httplib.h>

namespace cppwebsite::app
{
    App::App(Options options)
    : m_options(std::move(options))
    {}

    void
    App::start() const {
        httplib::Server server;

        pages::Index index;
        index.registerServer(server);

        server.listen(m_options.getHost().c_str(), m_options.getPort());
    }
} // namespace cppwebsite::app
