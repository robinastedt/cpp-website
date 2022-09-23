#include <httplib.h>

#include <cppwebsite/pages/Index.hh>

namespace cppwebsite
{
    int main() {
        httplib::Server server;

        pages::Index index;
        index.registerServer(server);

        server.listen("localhost", 8080);

        return EXIT_SUCCESS;
    }
} // namespace cppwebsite



int main() {
    return cppwebsite::main();
}