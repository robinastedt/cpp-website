#pragma once

#include <cppwebsite/dom/UniqueBase.hh>
#include <string>

namespace cppwebsite::dom
{
    struct Property;

    class Class : public UniqueBase<Class> {
        size_t m_index;

    public:
        Class(std::string name);

        const std::string& getPropertyName() const override;
    };
} // namespace cppwebsite::dom
