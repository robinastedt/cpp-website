#pragma once

#include <cppwebsite/dom/UniqueBase.hh>
#include <string>

namespace cppwebsite::dom
{
    class Id : public UniqueBase<Id> {
        friend class UniqueBase<Id>;
        Id(New);
        Id(Anonymous);

        static std::string_view getPropertyName();
        static std::string getStringRepresentation(size_t index);
    };
} // namespace cppwebsite::dom
