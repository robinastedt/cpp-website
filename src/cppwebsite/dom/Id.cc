#include "Id.hh"

#include <cppwebsite/dom/Property.hh>
#include <map>
#include <stdexcept>

namespace cppwebsite::dom
{
    Id::Id(std::string name)
    : UniqueBase<Id>(std::move(name))
    {}

    const std::string&
    Id::getPropertyName() const {
        static std::string name = "id";
        return name;
    }

} // namespace cppwebsite::dom


#include "cppwebsite/dom/UniqueBase.template.cc"
template class cppwebsite::dom::UniqueBase<cppwebsite::dom::Id>;