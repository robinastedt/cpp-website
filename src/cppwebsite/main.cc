
#include <cppwebsite/app/App.hh>
#include <cppwebsite/app/Options.hh>

int main(int argc, char** argv) {
    cppwebsite::app::Options options{argc, argv};
    if (options.getExitCode().has_value()) {
        return *options.getExitCode();
    }
    cppwebsite::app::App app{std::move(options)};
    app.start();
    return EXIT_SUCCESS;
}