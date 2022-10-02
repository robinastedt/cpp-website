#pragma once

#include <string>
#include <cppwebsite/common/EscapePolicy.hh>

namespace cppwebsite
{
    std::string escapeForHtml(std::string_view str, EscapePolicy escapePolicy = EscapePolicy::Default);
} // namespace cppwebsite
