#pragma once

#include <string>
#include <map>
#include <vector>

namespace cppwebsite::dom
{
    struct Property;

    template<typename T>
    class UniqueBase {
        size_t m_index;

        static std::map<std::string, size_t> _indices;
        static std::vector<std::string> _names;

    public:
        UniqueBase(std::string name);

        bool isAnonymous() const;
        Property getProperty() const;

        virtual const std::string& getPropertyName() const = 0;

        static T anonymous();

    };
} // namespace cppwebsite::dom
