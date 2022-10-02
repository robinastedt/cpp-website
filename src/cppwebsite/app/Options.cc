#include "Options.hh"

#include <boost/program_options.hpp>
#include <iostream>

namespace cppwebsite::app
{
    Options::Options(int argc, char** argv) {
        bool help = false;
        namespace po = boost::program_options;
        po::options_description desc{"Allowed options"};
        desc.add_options()
            ("help", po::bool_switch(&help), "produce help message")
            ("host", po::value(&m_host)->default_value("localhost"))
            ("port", po::value(&m_port)->default_value(8080));

        try {
            po::variables_map vm;
            po::store(po::parse_command_line(argc, argv, desc), vm);
            po::notify(vm);
            if (help) {
                std::cout << desc << std::endl;
                m_exitCode = 0;
            }
        } catch (const std::exception& ex) {
            std::cerr << ex.what() << std::endl;
            m_exitCode = 1;
        }
    }

    std::optional<int>
    Options::getExitCode() const {
        return m_exitCode;
    }

    const std::string&
    Options::getHost() const {
        return m_host;
    }

    uint16_t
    Options::getPort() const {
        return m_port;
    }

} // namespace cppwebsite::app
