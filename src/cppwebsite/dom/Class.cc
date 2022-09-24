#include "Class.hh"

#include <cppwebsite/dom/Property.hh>
#include <map>
#include <stdexcept>

namespace cppwebsite::dom
{
    Class::Class(std::string name)
    : UniqueBase<Class>(std::move(name))
    {}

    const std::string&
    Class::getPropertyName() const {
        static std::string name = "class";
        return name;
    }

} // namespace cppwebsite::dom


#include "cppwebsite/dom/UniqueBase.template.cc"
template class cppwebsite::dom::UniqueBase<cppwebsite::dom::Class>;