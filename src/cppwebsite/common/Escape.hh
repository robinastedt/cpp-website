#pragma once

#include <string>

namespace cppwebsite
{
    enum class EscapePolicy {
        Default,
        EscapeWhitespace
    };
    std::string escapeForHtml(std::string_view str, EscapePolicy escapePolicy = EscapePolicy::Default);
} // namespace cppwebsite
