#pragma once

#include <cppwebsite/app/Options.hh>

namespace cppwebsite::app
{
    class App {
        Options m_options;

    public:
        App(Options options);
        void start() const;
    };
} // namespace cppwebsite::app
