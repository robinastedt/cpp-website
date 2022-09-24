#include "UniqueBase.hh"

#include <cppwebsite/common/Property.hh>
#include <vector>

namespace cppwebsite::dom
{
    namespace
    {
        constexpr size_t _anon_index = 0;

        template<typename T>
        std::vector<std::string> _instances {
            {""}  // Anonymous instance, index = 0
        };

    } // namespace

    template<typename T>
    UniqueBase<T>::UniqueBase(New)
    : m_index(_instances<T>.size())
    {
        _instances<T>.emplace_back(T::getStringRepresentation(m_index));
    }

    template<typename T>
    UniqueBase<T>::UniqueBase(Anonymous)
    : m_index(_anon_index)
    {}

    template<typename T>
    bool
    UniqueBase<T>::isAnonymous() const {
        return m_index == _anon_index;
    }
    
    template<typename T>
    Property
    UniqueBase<T>::getProperty() const {
        return Property{std::string{T::getPropertyName()}, _instances<T>[m_index]};
    }

    template<typename T>
    T
    UniqueBase<T>::anonymous() {
        return T{Anonymous{}};
    }

    template<typename T>
    T
    UniqueBase<T>::createNew() {
        return T{New{}};
    }
    
} // namespace cppwebsite::dom
