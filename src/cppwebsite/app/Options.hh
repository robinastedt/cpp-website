#pragma once

#include <optional>
#include <string>

namespace cppwebsite::app
{
    class Options {
        std::optional<int> m_exitCode;
        std::string m_host;
        uint16_t m_port;

    public:
        Options(int argc, char** argv);

        std::optional<int> getExitCode() const;
        const std::string& getHost() const;
        uint16_t getPort() const;
    };
} // namespace cppwebsite::app
