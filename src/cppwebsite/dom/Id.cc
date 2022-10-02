#include "Id.hh"

namespace cppwebsite::dom
{
    Id::Id(New)
    : UniqueBase<Id>(New{})
    {}

    Id::Id(Anonymous)
    : UniqueBase<Id>(Anonymous{})
    {}

    std::string_view
    Id::getPropertyName() {
        return "id";
    }

    std::string
    Id::getStringRepresentation(size_t index) {
        return "id" + std::to_string(index);
    }

} // namespace cppwebsite::dom


#include "cppwebsite/dom/UniqueBase.template.cc"
template class cppwebsite::dom::UniqueBase<cppwebsite::dom::Id>;