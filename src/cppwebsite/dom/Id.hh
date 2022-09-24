#pragma once

#include <string_view>

namespace cppwebsite::dom
{
    struct Property;

    class Id {
        size_t m_index;

    public:
        Id(std::string name);

        bool isAnonymous() const;
        Property getProperty() const;

        static Id anonymous();
    };
} // namespace cppwebsite::dom
