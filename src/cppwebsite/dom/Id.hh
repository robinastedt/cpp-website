#pragma once

#include <cppwebsite/dom/UniqueBase.hh>
#include <string>

namespace cppwebsite::dom
{
    struct Property;

    class Id : public UniqueBase<Id> {
        size_t m_index;

    public:
        Id(std::string name);

        const std::string& getPropertyName() const override;
    };
} // namespace cppwebsite::dom
