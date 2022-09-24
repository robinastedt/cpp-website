#include "Class.hh"

namespace cppwebsite::dom
{
    Class::Class(New)
    : UniqueBase<Class>(New{})
    {}

    Class::Class(Anonymous)
    : UniqueBase<Class>(Anonymous{})
    {}

    std::string_view
    Class::getPropertyName() {
        return "class";
    }

    std::string
    Class::getStringRepresentation(size_t index) {
        return ".class" + std::to_string(index);
    }


} // namespace cppwebsite::dom


#include "cppwebsite/dom/UniqueBase.template.cc"
template class cppwebsite::dom::UniqueBase<cppwebsite::dom::Class>;