#pragma once

#include <string>
#include <vector>

namespace cppwebsite
{
    struct Property {
        std::string key;
        std::string value;
    };

    using Properties = std::vector<Property>;
} // namespace cppwebsite
