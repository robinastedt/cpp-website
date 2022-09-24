#pragma once

#include <cstddef>

namespace cppwebsite
{
    struct Property;
} // namespace cppwebsite


namespace cppwebsite::dom
{
    template<typename T>
    class UniqueBase {
        size_t m_index;

    protected:
        struct Anonymous {};
        struct New {};

        UniqueBase(Anonymous);
        UniqueBase(New);
    public:
        // Deriving class/template argument needs to implement the following:
        // static std::string_view getPropertyName();
        // static std::string getStringRepresentation(size_t index);

        bool isAnonymous() const;

        Property getProperty() const;

        static T anonymous();
        static T createNew();
    };
} // namespace cppwebsite::dom
