#pragma once

#include <cppwebsite/dom/UniqueBase.hh>
#include <string>

namespace cppwebsite::dom
{
    class Class : public UniqueBase<Class> {
        friend class UniqueBase<Class>;
        Class(New);
        Class(Anonymous);

        static std::string_view getPropertyName();
        static std::string getStringRepresentation(size_t index);
    };
} // namespace cppwebsite::dom
