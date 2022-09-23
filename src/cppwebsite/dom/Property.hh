#pragma once

#include <string>
#include <vector>

namespace cppwebsite::dom
{
    struct Property {
        std::string key;
        std::string value;
    };

    using Properties = std::vector<Property>;
} // namespace cppwebsite::dom
